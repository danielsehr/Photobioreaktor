#pragma once

#include "storage/StorageMananger.h"
#include "settings/SettingsManager.h"
#include "network/NetworkManager.h"
#include "web/WebSocketManager/WebSocketManager.h"
#include "time/RTCManager.h"
#include "services/SensorService/SensorService.h"
#include "web/WebServerManager/WebServerManager.h"
// #include "services/DashboardService/DashboardService.h"
// #include "services/ExperimentService/ExperimentService.h"


class App
{
    public:
        App();

        void begin();

        void update();

    private:
        StorageManager storageManager_;

        SettingsManager settingsManager_;

        NetworkManager networkManager_;

        WebSocketManager webSocketManager_;

        RTCManager rtcManager_; 

        // ExperimentService experimentService_;
        
        // DashboardService dashboardService_;
        
        SensorService sensorService_;
        
        WebServerManager webServerManager_;
};