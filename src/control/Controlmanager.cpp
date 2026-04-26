#include "control/ControlManager.h"
#include "config/SystemConfig.h"

void ControlManager::update(const SensorData& data, const SystemSettings& settings) {
    controlTemperature(data, settings);
    controlStirring(settings);
    controlLight(settings);
}


void ControlManager::controlTemperature(const SensorData& data, const SystemSettings& settings) {
    // Check waterlevel and temp
    bool waterOk = data.waterLevel > 50;
    bool tempValid = data.temperature > 0;

    if (waterOk && tempValid) 
    {
        if (data.temperature < settings.minTemp)
        {
            digitalWrite(Config::PIN_HEATER,HIGH);
        }
        else if (data.temperature > settings.maxTemp)
        {
            digitalWrite(Config::PIN_HEATER, LOW);
        }
    }
    else
    {
        digitalWrite(Config::PIN_HEATER, LOW);
    }
}

void ControlManager::controlStirring(const SystemSettings& settings) {
    unsigned long now = millis();

    if (!stirringActive && now - lastStirTime >= settings.stirIntervalMinutes)
    {
        stirringActive = true;
        stirStartTime = now;
        digitalWrite(Config::PIN_STIRRER, HIGH);
    }
    
    if (stirringActive && now - stirStartTime >= settings.stirDurationMinutes)
    {
        stirringActive = false;
        lastStirTime = now;
        digitalWrite(Config::PIN_STIRRER, LOW);        
    }
}

void ControlManager::controlLight(const SystemSettings& settings) {
    int hour = 0; // later from RTC

    if (hour >= settings.lightOnHour && hour < settings.lightOffHour)
    {
        digitalWrite(Config::PIN_LIGHT, HIGH);
    }
    else 
    {
        digitalWrite(Config::PIN_LIGHT, LOW);
    }
    
}
