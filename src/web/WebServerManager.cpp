#include "web/WebServerManager.h"

#include <ArduinoJson.h>
#include <LittleFS.h>


WebServerManager::WebServerManager(

    SettingsManager& settingsMgr,
    SensorManager& sensorMgr,
    StorageManager& storageMgr,
    RTCManager& rtcMgr)
    : settingsManager(settingsMgr),
    sensorManager(sensorMgr),
    storageManager(storageMgr),
    rtcManager(rtcMgr) 
{
}


void WebServerManager::begin(){
    setupRoutes();

    server.begin();
}


void WebServerManager::setupRoutes()
{
    server.on("/", HTTP_GET, [](AsyncWebServerRequest* request)
    {
        request->send(
            LittleFS,
            "/index.html",
            "text/html"
        );
    });
    

    server.serveStatic("/", LittleFS, "/");

    server.on("/settings.json", HTTP_GET, [this](AsyncWebServerRequest* request)
    {
        handleSettingsGet(request);
    });


    server.on("/data.json", HTTP_GET, [this](AsyncWebServerRequest* request)
    {
        handleSensorData(request);
    });

    server.on("/download", HTTP_GET, [this](AsyncWebServerRequest* request)
    {
        handleCsvDownload(request);
    });
}


void WebServerManager::handleSettingsGet(AsyncWebServerRequest* request)
{
    JsonDocument doc;

    const auto& settings = settingsManager.getSettings();
    
    doc["maxTemp"] = settings.maxTemp;
    doc["minTemp"] = settings.minTemp;
    doc["stirInterval"] = settings.stirIntervalMinutes;
    doc["stirDuration"] = settings.stirDurationMinutes;
    doc["lightOn"] = settings.lightOnHour;
    doc["lightOff"] = settings.lightOffHour;
    doc["measurementInterval"] = settings.measurementIntervalSeconds;

    String json;
    serializeJson(doc, json);

    request->send(200, "application/json", json);
}


void WebServerManager::handleSensorData(AsyncWebServerRequest* request)
{
    JsonDocument doc;

    const auto& data = sensorManager.getData();

    doc["uptimeSeconds"] = data.uptimeSeconds;
    doc["temperature"] = data.temperature;
    doc["conductivity"] = data.conductivity;
    doc["turbidity"] = data.turbidity;
    doc["waterLevel"] = data.waterLevel;

    String json;
    serializeJson(doc, json);

    request->send(200, "application/json", json);
}


void WebServerManager::handleCsvDownload(AsyncWebServerRequest* request)
{
    request->send(
        LittleFS,
        "/data.csv",
        "text/csv",
        true
    );
}