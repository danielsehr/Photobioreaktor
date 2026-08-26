#include "app.h"
#include "utils/logger/Logger.h"

App::App()
    : 
    storageManager_(),
    settingsManager_(),
    networkManager_(),
    webSocketManager_(),
    sensorService_(),
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

    // storageManager_.listDirectory("/experiments");

    LOG_INFO("Done.");
}