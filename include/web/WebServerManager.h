#pragma once

#include <ESPAsyncWebServer.h>

#include "core/SystemTypes.h"
#include "settings/SettingsManager.h"
#include "sensors/SensorManager.h"
#include "storage/StorageMananger.h"
#include "time/RTCManager.h"

class WebServerManager 
{
public:
    // Constructor: blueprint how the class is constructed
    WebServerManager(
        SettingsManager& settingsManager,
        SensorManager& sensorManager,
        StorageManager& storageManager,
        RTCManager& rtcManager
    );

    void begin();

private:
    AsyncWebServer server{80};
    
    // Member variables of the class -> storage location inside object
    SettingsManager& settingsManager;
    SensorManager& sensorManager;
    StorageManager& storageManager;
    RTCManager& rtcManager;

    void setupRoutes();

    void handleSettingsGet(AsyncWebServerRequest* request);
    void handleSettingsPost(AsyncWebServerRequest* request,
                            uint8_t* data,
                            size_t len);

    void handleSensorData(AsyncWebServerRequest* request);
    
    void handleCsvDownload(AsyncWebServerRequest* request);
};