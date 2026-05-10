#include "network/NetworkManager.h"
#include "config/SystemConfig.h"

#include <WiFi.h>
#include <Arduino.h>


void NetworkManager::begin()
{
    WiFi.mode(WIFI_AP);

    bool success = WiFi.softAP(
        Config::AP_SSID,
        Config::AP_PASSWORD
    );

    if (!success)
    {
        Serial.println("SoftAP start failed!");
        return;
    }

    IPAddress ip = WiFi.softAPIP();

    snprintf(
        ipBuffer,
        sizeof(ipBuffer),
        "%u.%u.%u.%u",
        ip[0], ip[1], ip[2], ip[3]
    );

    Serial.print("AP IP: ");
    Serial.println(ipBuffer);
}