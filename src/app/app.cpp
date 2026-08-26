#include "app.h"
#include "utils/logger/Logger.h"

App::App()
    : 
    storageManager_(),
    settingsManager_(),
    networkManager_(),
    webSocketManager_(),
    sensorService_(),
    experimentService_(),
    dashboardService_(webSocketManager_),
    webServerManager_(
        settingsManager_, 
        sensorService_, 
        storageManager_,
        rtcManager_,
        webSocketManager_
    )
{
}

void App::begin()
{
    Logger::begin();

    storageManager_.begin();
    
    networkManager_.begin();
    
    webServerManager_.begin();
    
    sensorService_.begin();

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
        const SensorData& measurement = sensorService_.latestMeasurement();

        // dashboardService_.publishMeasurement(measurement);

        // experimentService_.record(measurement);
    }

    if (webSocketManager_.hasNewClient())
    {
        // dashboardService_.publishHistory(*webSocketManager_.newClient());

        webSocketManager_.clearNewClient();
    }

    sensorService_.clearNewMeasurement();
}