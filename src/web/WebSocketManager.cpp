#include "web/WebSocketManager.h"

WebSocketManager::WebSocketManager(SensorManager& sensorMgr)
    : sensorManager(sensorMgr), ws("/ws") {}


void WebSocketManager::begin(AsyncWebServer& server)
{
    ws.onEvent([this](AsyncWebSocket *server,
                      AsyncWebSocketClient *client,
                      AwsEventType type,
                      void *arg,
                      uint8_t *data,
                      size_t len)
    {
        if (type == WS_EVT_CONNECT) {
            // optional: send initial state
            broadcastSensorData();
        }
    });

    server.addHandler(&ws);
}


void WebSocketManager::broadcastSensorData()
{
    const auto& data = sensorManager.getData();

    JsonDocument doc;
    doc["uptimeSeconds"] = data.uptimeSeconds;
    doc["temperature"] = data.temperature;
    doc["conductivity"] = data.conductivity;
    doc["turbidity"] = data.turbidity;
    doc["waterLevel"] = data.waterLevel;

    String json;
    serializeJson(doc, json);

    ws.textAll(json);
}