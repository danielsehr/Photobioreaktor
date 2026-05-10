#include "web/WebSocketManager.h"

// Constructor 
WebSocketManager::WebSocketManager(SensorManager& sensorMgr)
    : sensorManager(sensorMgr), 
      ws("/ws") 
      {}


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
            // Initial sensor values send
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

    // Send json as text websocket message to all connected clients
    ws.textAll(json);
}