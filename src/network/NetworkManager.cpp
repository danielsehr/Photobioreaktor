#include <WiFi.h>
#include "NetworkManager.h"
#include "config/SystemConfig.h"
#include "utils/logger/Logger.h"

void NetworkManager::begin()
{
    initializeAP();
}

void NetworkManager::initializeAP()
{
    LOG_INFO("Start access point...");


    WiFi.mode(WIFI_AP);

    if (!WiFi.softAP(Config::AP_NAME, Config::AP_PASSWORD))
    {
        LOG_ERROR("Failed to start AP.");
        return;
    }


    LOG_INFO("AP started.");
    LOG_INFO(WiFi.softAPIP().toString().c_str());
}