#pragma once
#include "config/SystemConfig.h"
#include "core/SensorData.h"
#include "web/WebSocketManager/WebSocketManager.h"
#include "utils/RingBuffer/RingBuffer.h"

class DashboardService
{
public: 
    explicit DashboardService(WebSocketManager& socket);

    void publishMeasurement(const SensorData& data);
    
    void publishHistory(AsyncWebSocketClient& client);
    
private:
    WebSocketManager& webSocketManager_;
    
    RingBuffer<SensorData, Config::RING_BUFFER_SIZE> history_;
    
    void serializeMeasurement(const SensorData& data, char* buffer, std::size_t bufferSize) const;

    void sendHistoryBegin(AsyncWebSocketClient& client);

    void sendHistoryEnd(AsyncWebSocketClient& client);
};