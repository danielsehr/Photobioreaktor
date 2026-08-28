#include "app.h"
#include "utils/logger/Logger.h"

App::App()
    : 
    rtcManager_(),
    storageManager_(),
    settingsManager_(),

    networkManager_(),
    webSocketManager_(),

    sensorService_(),
    controlService_(),

    experimentService_(storageManager_),
    dashboardService_(webSocketManager_),
    webServerManager_(
        rtcManager_,
        webSocketManager_,
        experimentService_,
        storageManager_,
        settingsManager_
    )
{
}

void App::begin()
{
    Logger::begin();
    rtcManager_.begin();

    storageManager_.begin();
    
    networkManager_.begin();
    
    webServerManager_.begin();
    
    sensorService_.begin();

    settingsManager_.begin();

    LOG_INFO("Application started.");

    LOG_INFO("Printing filesystem:");

    storageManager_.listDirectory("/experiments");

    LOG_INFO("Done.");
}


void App::update()
{
    sensorService_.update();

    if (sensorService_.hasNewMeasurement())
    {
        LOG_INFO("RTC Date: %s", rtcManager_.getDate());
        LOG_INFO("RTC Time: %s", rtcManager_.getTime());
        
        const SensorData& measurement = sensorService_.latestMeasurement();

        controlService_.update(
            measurement, 
            settingsManager_.getSettings(), 
            rtcManager_.getHour()
        );
        
        dashboardService_.publishMeasurement(measurement);

        experimentService_.record(measurement);
    }

    if (webSocketManager_.hasNewClient())
    {
        dashboardService_.publishHistory(*webSocketManager_.newClient());

        webSocketManager_.clearNewClient();
    }

    sensorService_.clearNewMeasurement();
}