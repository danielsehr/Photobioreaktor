#pragma once

#include "sensors/SensorManager.h"
#include <ESPAsyncWebServer.h>

class WebSocketManager {
public:
    WebSocketManager(SensorManager& sensorMgr);

    void begin(AsyncWebServer& server);
    void broadcastSensorData();

private:
    // Member variables
    SensorManager& sensorManager;
    AsyncWebSocket ws;
};