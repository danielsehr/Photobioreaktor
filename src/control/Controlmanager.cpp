#include <iostream>
#include "control/ControlManager.h"
#include "config/SystemConfig.h"

void ControlManager::update(
    const SensorData& data,
    const SystemSettings& settings,
    int currenHour
    )
{
    controlTemperature(data, settings);
    controlStirring(settings);
    controlLight(settings);
}


void ControlManager::controlTemperature(const SensorData& data, const SystemSettings& settings) {
    const bool waterOk  = data.waterLevel > 50;
    const bool tempValid = data.temperature > 0;

    bool shouldHeat = false;

    if (waterOk && tempValid)
    {
        if (data.temperature < settings.minTemp)
        {
            shouldHeat = true;
        }
        else if (data.temperature > settings.maxTemp)
        {
            shouldHeat = false;
        }
        else
        {
            shouldHeat = heaterActive;
        }
    }
    else
    {
        std::cout << "ControlManager: Invalid water level or temperature!\n";
        shouldHeat = false;
    }

    
    if (shouldHeat != heaterActive)
    {
        heaterActive = shouldHeat;

        digitalWrite(
            Config::PIN_HEATER,
            heaterActive ? HIGH : LOW);

        if (heaterActive)
        {
            std::cout << "ControlManager: Heater ON\n";
        }
        else
        {
            std::cout << "ControlManager: Heater OFF\n";
        }
    }
}


void ControlManager::controlStirring(const SystemSettings& settings) {
    constexpr unsigned long MS_PER_MINUTE = 60UL * 1000UL;

    const unsigned long stirIntervalMs =
        static_cast<unsigned long>(settings.stirIntervalMinutes) * MS_PER_MINUTE;
    
    const unsigned long stirDurationMs =
        static_cast<unsigned long>(settings.stirDurationMinutes) * MS_PER_MINUTE;

    unsigned long now = millis();


    if (!stirringActive && now - lastStirTime >= stirIntervalMs)
    {
        stirringActive = true;
        stirStartTime = now;
        digitalWrite(Config::PIN_STIRRER, HIGH);
    }
    
    if (stirringActive && now - stirStartTime >= stirDurationMs)
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
