#pragma once

#include <ESPAsyncWebServer.h>


class WebSocketManager
{
public:
    WebSocketManager() = default;

    void begin(AsyncWebServer& server);

    void broadcast(const char* message);

    void send(AsyncWebSocketClient& client, const char* message);

    bool hasNewClient() const;

    AsyncWebSocketClient* newClient();

    void clearNewClient();
    
private:
    AsyncWebSocket webSocket_{"/ws"};

    AsyncWebSocketClient* newClient_ = nullptr;

    void onEvent(
        AsyncWebSocket* server,
        AsyncWebSocketClient* client,
        AwsEventType type,
        void* arg,
        uint8_t* data,
        size_t len
    );
};