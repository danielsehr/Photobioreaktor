#include "storage/StorageMananger.h"
#include "config/SystemConfig.h"
#include <LittleFS.h>
#include <Arduino.h>


bool StorageManager::begin() {
    if (!LittleFS.begin(true))
    {
        Serial.println("LittleFS mount failed!");
        return false;
    }

    return createCsvIfMissing();
}

bool StorageManager::createCsvIfMissing() {
    if (LittleFS.exists(Config::DATA_FILE))
        return true;

    File file = LittleFS.open(Config::DATA_FILE, "w");
    if(!file)
        return false;

    // Initial write of headers and close file
    file.println("uptime,temp,conductivity,turbidity,water_level,date,time");
    file.close();
}

bool StorageManager::appendMeasurement(const SensorData& data,
                                       const char* date,
                                       const char* time) 
{
    File file = LittleFS.open(Config::DATA_FILE, "a");
    if(!file)
    {
        Serial.println("CSV open failed!");
        return false;
    }

    file.printf("%lu,%.2f,%.2f,%.2f,%d,%s,%s\n",
                data.uptimeSeconds,
                data.temperature,
                data.conductivity,
                data.turbidity,
                data.waterLevel,
                date,
                time);

    file.close();
    return true;
}
