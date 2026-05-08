#pragma once

#include <ESPAsyncWebServer.h>

#include "storage/SettingsManager.h"
#include "sensors/SensorManager.h"
#include "storage/StorageMananger.h"
#include "time/RTCManager.h"

class WebServerManager 
{
public:
    WebServerManager(
        SettingsManager& settingsManager,
        SensorManager& SensorManager,
        StorageManager& StorageManager,
        RTCManager& rtcManager
    );

    void begin();

private:
    AsyncWebServer server{80};

    SettingsManager& settingsManager;
    SensorManager& SensorManager;
    StorageManager& StorageManager;
    RTCManager& rtcManager;

    void setupRoutes();

    void handleSettingsGet(AsyncWebServerRequest* request);
    void handleSettingsPost(AsyncWebServerRequest* request,
                            uint8_t* data,
                            size_t len);

    void handleSensorData(AsyncWebServerRequest* request);
    
    void handleCsvDownload(AsyncWebServerRequest* request);
};