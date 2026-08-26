#include "WebSocketManager.h"
#include "utils/logger/Logger.h"


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


void WebSocketManager::onEvent(
    AsyncWebSocket* server,
    AsyncWebSocketClient* client,
    AwsEventType type,
    void* arg,
    uint8_t* data,
    size_t len)
{
    switch (type)
    {
    case WS_EVT_CONNECT:
        {
            LOG_INFO("Client connected.");
        
            newClient_ = client;
            
            break;
        }

    case WS_EVT_DISCONNECT:
        {
            LOG_INFO("Client disconnected.");
        
            if (newClient_ == client)
                {
                    newClient_ = nullptr;
                }

            break;
        }
        

    case WS_EVT_DATA:
    {
        if (data == nullptr || len == 0)
            break;

        LOG_INFO("%.*s", static_cast<int>(len),
                reinterpret_cast<const char*>(data));

        client->text("Message received.");

        break;
    }

    default:
        break;
    }
}

void WebSocketManager::broadcast(const char *message)
{
    webSocket_.textAll(message);
}

void WebSocketManager::send(AsyncWebSocketClient& client, const char* message)
{
    client.text(message);
}

bool WebSocketManager::hasNewClient() const 
{
    return newClient_ != nullptr;
}

AsyncWebSocketClient* WebSocketManager::newClient()
{
    return newClient_;
}

void WebSocketManager::clearNewClient()
{
    newClient_ = nullptr;
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