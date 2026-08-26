#pragma once

#include <ESPAsyncWebServer.h>

#include "core/SystemTypes.h"
#include "settings/SettingsManager.h"
#include "services/SensorService/SensorService.h"
#include "storage/StorageManager.h"
#include "time/RTCManager.h"
#include "web/WebSocketManager/WebSocketManager.h"


class WebServerManager 
{
public:
    WebServerManager(
        SettingsManager& settingsManager,
        SensorService& sensorService,
        StorageManager& storageManager,
        RTCManager& rtcManager,
        WebSocketManager& webSocketManager
    );

    void begin();

private:
    AsyncWebServer server{80};
    
    // Member variables of the class -> storage location inside object
    SettingsManager& settingsManager;
    SensorService& sensorService;
    StorageManager& storageManager;
    RTCManager& rtcManager;
    WebSocketManager& webSocketManager;

    void setupRoutes();
};