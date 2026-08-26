#pragma once

#include <ESPAsyncWebServer.h>

#include "core/SystemTypes.h"
#include "settings/SettingsManager.h"
#include "services/SensorService/SensorService.h"
#include "storage/StorageManager.h"
#include "time/RTCManager.h"
#include "web/WebSocketManager/WebSocketManager.h"
#include "services/ExperimentService/ExperimentService.h"

class WebServerManager 
{
public:
    explicit WebServerManager(
        WebSocketManager& webSocketManager,
        ExperimentService& experimentService,
        StorageManager& storageManager
    );

    void begin();

private:
    AsyncWebServer server_{Config::HTTP_PORT};
    
    StorageManager& storageManager_;

    WebSocketManager& webSocketManager_;

    ExperimentService& experimentService_;

    void registerRoutes();

    void handleStartExperiment(AsyncWebServerRequest* request);
    void handleStopExperiment(AsyncWebServerRequest* request);
    void handleExperimentStatus(AsyncWebServerRequest* request);
    void handleListExperiments(AsyncWebServerRequest* request);

    void handleDownloadCsv(AsyncWebServerRequest* request);
};