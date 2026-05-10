#pragma once

#include "sensors/SensorManager.h"
#include <ESPAsyncWebServer.h>

class WebSocketManager {
public:
    WebSocketManager(SensorManager& sensorMgr);

    void begin(AsyncWebServer& server);
    void loop(); // optional

    void broadcastSensorData();

private:
    SensorManager& sensorManager;

    AsyncWebSocket ws;
};