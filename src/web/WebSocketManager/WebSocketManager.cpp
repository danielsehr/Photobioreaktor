#include "WebSocketManager.h"
#include "utils/logger/Logger.h"

// Constructor 
WebSocketManager::WebSocketManager(SensorManager& sensorMgr)
    : sensorManager(sensorMgr), 
      ws("/ws") 
      {}


void WebSocketManager::begin(AsyncWebServer& server)
{
    webSocket_.onEvent(
        [this](
            AsyncWebSocket* server,
            AsyncWebSocketClient* client,
            AwsEventType type,
            void* arg,
            uint8_t* data,
            size_t len
        )
        {
            onEvent(server, client, type, arg, data, len);
        }

    );

    server.addHandler(&webSocket_);

    LOG_INFO("Websocket initialized.");
}


// void WebSocketManager::broadcastSensorData()
// {
//     const auto& data = sensorManager.getData();

//     JsonDocument doc;
//     doc["uptimeSeconds"] = data.uptimeSeconds;
//     doc["temperature"] = data.temperature;
//     doc["conductivity"] = data.conductivity;
//     doc["turbidity"] = data.turbidity;
//     doc["waterLevel"] = data.waterLevel;

//     String json;
//     serializeJson(doc, json);

//     // Send json as text websocket message to all connected clients
//     ws.textAll(json);
// }