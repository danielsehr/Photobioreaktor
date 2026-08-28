#include <ArduinoJson.h>
#include <LittleFS.h>
#include "web/WebServerManager/WebServerManager.h"
#include "utils/logger/Logger.h"

WebServerManager::WebServerManager(
    RTCManager& rtcManager,
    WebSocketManager& webSocketManager,
    ExperimentService& experimentService,
    StorageManager& storageManager,
    SettingsManager& settingsManager
    ) : rtcManager_(rtcManager),
        webSocketManager_(webSocketManager),
        experimentService_(experimentService),
        storageManager_(storageManager),
        settingsManager_(settingsManager)
{
}

void WebServerManager::begin()
{
    registerRoutes();

    server_.serveStatic("/", LittleFS, "/");

    webSocketManager_.begin(server_);

    server_.begin();

    LOG_INFO("HTTP server initialized.");
}

void WebServerManager::registerRoutes()
{
    server_.on("/", HTTP_GET,
               [](AsyncWebServerRequest *request)
               {
                   request->send(LittleFS, "/index.html", "text/html");
               });

    server_.on("/api/experiment/start", HTTP_POST,
               [this](AsyncWebServerRequest *request)
               {
                   handleStartExperiment(request);
               });

    server_.on("/api/experiment/stop", HTTP_POST,
               [this](AsyncWebServerRequest *request)
               {
                   handleStopExperiment(request);
               });

    server_.on("/api/experiment/status", HTTP_GET,
               [this](AsyncWebServerRequest *request)
               {
                   handleExperimentStatus(request);
               });

    server_.on("/api/experiment/download", HTTP_GET,
               [this](AsyncWebServerRequest *request)
               {
                   handleDownloadCsv(request);
               });

    server_.on("/api/experiments", HTTP_GET,
               [this](AsyncWebServerRequest *request)
               {
                   handleListExperiments(request);
               });

    server_.on("/api/settings", HTTP_GET,
               [this](AsyncWebServerRequest *request)
               {
                   handleGetSettings(request);
               });

    server_.on("/api/settings", HTTP_PUT,
               [this](AsyncWebServerRequest *request)
               {
               },
               nullptr,
               [this](AsyncWebServerRequest* request, uint8_t* data, size_t len, size_t index, size_t total)
                {
                    handlePutSettings(request, data, len, index, total);
                }
            );

    server_.on("/api/time", HTTP_PUT,
               [this](AsyncWebServerRequest *request)
               {
               },
               nullptr,
               [this](AsyncWebServerRequest* request, uint8_t* data, size_t len, size_t index, size_t total)
                {
                    handlePutTime(request, data, len, index, total);
                }
            );
            
}

void WebServerManager::handleStartExperiment(AsyncWebServerRequest *request)
{
    if (!experimentService_.start(nullptr))
    {
        request->send(409, "text/plain", "Could not start experiment.");
        return;
    }

    request->send(200, "text/plain", "Experiment started.");
}

void WebServerManager::handleStopExperiment(AsyncWebServerRequest *request)
{
    experimentService_.stop();

    request->send(200, "text/plain", "Experiment stopped.");
}

void WebServerManager::handleExperimentStatus(AsyncWebServerRequest *request)
{
    const bool recording = experimentService_.isRecording();

    if (recording)
    {
        request->send(200, "application/json", R"({"recording":true})");
    }
    else
    {
        request->send(200, "application/json", R"({"recording":false})");
    }
}

void WebServerManager::handleListExperiments(AsyncWebServerRequest *request)
{
    uint32_t ids[Config::MAX_EXPERIMENTS];

    const std::size_t count = storageManager_.listExperimentIds(ids, Config::MAX_EXPERIMENTS);

    JsonDocument json;
    JsonArray experiments = json.to<JsonArray>();

    for (std::size_t i = 0; i < count; i++)
    {
        JsonObject experiment = experiments.add<JsonObject>();

        experiment["id"] = ids[i];
    }

    char response[Config::JSON_CAPACITY];

    const std::size_t length = serializeJson(
        json,
        response,
        sizeof(response));

    if (length == 0)
    {
        LOG_ERROR("[WebServerManager] Failed to serialize experiment list.");
        request->send(500, "text/plain", "[WebServerManager] Failed to serialize experiment list.");
        return;
    }

    request->send(200, "application/json", response);
}

void WebServerManager::handleDownloadCsv(AsyncWebServerRequest *request)

{
    if (!request->hasParam("id"))
    {
        request->send(400, "text/plain", "Missing experiment ID.");
        return;
    }

    const char *idString = request->getParam("id")->value().c_str();

    char *end = nullptr;

    const unsigned long id = strtoul(idString, &end, 10);

    if (*idString == '\0' || *end != '\0')
    {
        request->send(400, "text/plain", "Invalid experiment ID");
        return;
    }

    Experiment experiment{};
    experiment.id = static_cast<uint32_t>(id);

    char path[Config::CSV_PATH_MAX];

    if (!storageManager_.createCsvPath(experiment, path))
    {
        LOG_ERROR("Failed to generate experiment CSV path.");
        request->send(500, "text/plain", "Failed to generate file path.");
        return;
    }

    File file = LittleFS.open(path, FILE_READ);

    if (!file)
    {
        LOG_ERROR("Experiment file not found: %s", path);
        request->send(404, "text/plain", "Experiment file not found.");
        return;
    }

    request->send(file, path, "text/csv", true);
}

void WebServerManager::handleGetSettings(AsyncWebServerRequest *request)
{
    const SystemSettings& settings = settingsManager_.getSettings();

    JsonDocument json;

    json["maximalTemperatureCelcius"] =
        settings.maximalTemperatureCelcius;

    json["minimalTemperatureCelcius"] =
        settings.minimalTemperatureCelcius;

    json["stirringIntervalMinutes"] =
        settings.stirringIntervalMinutes;

    json["stirringDurationMinutes"] =
        settings.stirringDurationMinutes;

    json["lightOnHour"] =
        settings.lightOnHour;

    json["lightOffHour"] =
        settings.lightOffHour;

    json["measurementIntervalSeconds"] =
        settings.measurementIntervalSeconds;
    
    
    char response[Config::JSON_CAPACITY];

    std::size_t length =  serializeJson(json, response, sizeof(response));

    if (length == 0)
    {
        LOG_ERROR("[WebServerManager] Failed to serialize SystemSettings.");
        request->send(500, "text/plain", "[WebServerManager] Failed to serialize SystemSettings.");
        return;
    }

    request->send(200, "application/json", response);
}

void WebServerManager::handlePutSettings(AsyncWebServerRequest* request, uint8_t* data, size_t len, size_t index, size_t total)
{
    if (index != 0 || len != total) 
    {
        request->send(400, "text/plain", "[WebServerManager] Request body received in multiple chunks.");
        LOG_ERROR("[WebServerManager] Request body received in multiple chunks.");
        return;
    }

    JsonDocument json;
    
    const auto error = deserializeJson(json, data, len);

    if (error)
    {
        request->send(400, "text/plain", "Invalid JSON.");
        LOG_ERROR("[WebServerManager] Invalid JSON.");
        return;
    }
    

    SystemSettings settings;

    settings.maximalTemperatureCelcius = json["maximalTemperatureCelcius"];

    settings.minimalTemperatureCelcius = json["minimalTemperatureCelcius"];

    settings.stirringIntervalMinutes = json["stirringIntervalMinutes"];

    settings.stirringDurationMinutes = json["stirringDurationMinutes"];

    settings.lightOnHour = json["lightOnHour"];

    settings.lightOffHour = json["lightOffHour"];

    settings.measurementIntervalSeconds = json["measurementIntervalSeconds"];

    if (!settingsManager_.update(settings))
    {
        request->send(500, "text/plain", "[WebServerManager] Failed to save settings.");
        LOG_ERROR("[WebServerManager] Failed to save settings.");
        return;
    }

    request->send(200, "application/json", R"({"status":"ok"})");
    LOG_INFO("[WebServerManager] Saved new settings.");
}

void WebServerManager::handlePutTime(AsyncWebServerRequest* request, uint8_t* data, size_t len, size_t index, size_t total)
{
    JsonDocument json;

    const auto error = deserializeJson(json, data, len);

    if (error)
    {
        request->send(400, "text/plain", "Invalid JSON.");
        return;
    }

    if (!json["date"].is<const char*>() || !json["time"].is<const char*>())
    {
        request->send(400, "text/plain", "Missing date or time.");
        return;
    }

    const char* date = json["date"];

    const char* time = json["time"];

    Serial.println("WebServerManager, data and time: ");
    Serial.println(date);
    Serial.println(time);

    if (!rtcManager_.setDateTime(date, time))
    {
        request->send(400, "text/plain", "Invalid date or time.");
        return;
    }

    request->send(200, "application/json", R"({"status":"ok"})");
}