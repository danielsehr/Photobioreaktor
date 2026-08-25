#pragma once

#include <ESPAsyncWebServer.h>

#include "core/SystemTypes.h"
#include "settings/SettingsManager.h"
#include "sensors/SensorManager.h"
#include "storage/StorageMananger.h"
#include "time/RTCManager.h"
#include "web/WebSocketManager.h"


class WebServerManager 
{
public:
    // Constructor: blueprint how the class is constructed
    WebServerManager(
        SettingsManager& settingsManager,
        SensorManager& sensorManager,
        StorageManager& storageManager,
        RTCManager& rtcManager,
        WebSocketManager& webSocketManager
    );

    void begin();

private:
    AsyncWebServer server{80};
    
    // Member variables of the class -> storage location inside object
    SettingsManager& settingsManager;
    SensorManager& sensorManager;
    StorageManager& storageManager;
    RTCManager& rtcManager;
    WebSocketManager& webSocketManager;

    void setupRoutes();
};