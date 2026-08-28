#pragma once

#include "storage/StorageManager.h"
#include "settings/SettingsManager.h"
#include "network/NetworkManager.h"
#include "web/WebSocketManager/WebSocketManager.h"
#include "time/RTCManager.h"
#include "services/SensorService/SensorService.h"
#include "services/ControlService/ControlService.h"
#include "web/WebServerManager/WebServerManager.h"
#include "services/DashboardService/DashboardService.h"
#include "services/ExperimentService/ExperimentService.h"


class App
{
    public:
        App();

        void begin();

        void update();

    private:
        RTCManager rtcManager_; 
        
        StorageManager storageManager_;

        SettingsManager settingsManager_;

        NetworkManager networkManager_;

        WebSocketManager webSocketManager_;

        SensorService sensorService_;

        ControlService controlService_;
        
        ExperimentService experimentService_;
        
        DashboardService dashboardService_;
        
        WebServerManager webServerManager_;
};