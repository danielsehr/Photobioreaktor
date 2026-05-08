#include <iostream>
#include "control/ControlManager.h"
#include "config/SystemConfig.h"

void ControlManager::update(
    const SensorData& data,
    const SystemSettings& settings,
    int currentHour
    )
{
    controlTemperature(data, settings);
    controlStirring(settings);
    controlLight(settings, currentHour);
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

    bool shouldStir = stirringActive;

    if (!stirringActive && now - lastStirTime >= stirIntervalMs)
    {
        shouldStir = true;
        stirStartTime = now;
        
    }
    
    if (stirringActive && now - stirStartTime >= stirDurationMs)
    {
        shouldStir = false;
        lastStirTime = now;
    }


    if (shouldStir != stirringActive) 
    {
        stirringActive = shouldStir;

        digitalWrite(
            Config::PIN_STIRRER,
            stirringActive ? HIGH : LOW
        );
        
        if (stirringActive)
        {
            std::cout << "ControlManager: Stirring ON\n";
        }
        else
        {
            std::cout << "ControlManager: Stirring OFF\n";
        }
    }
}


void ControlManager::controlLight(const SystemSettings& settings, int currentHour) {

    bool shouldLight = lightActive;

    if (currentHour >= settings.lightOnHour && currentHour < settings.lightOffHour)
    {
        shouldLight = true;
        // digitalWrite(Config::PIN_LIGHT, HIGH);
    }
    else 
    {
        shouldLight = false;
        // digitalWrite(Config::PIN_LIGHT, LOW);
    } 

    if (shouldLight != lightActive) 
    {
        lightActive = shouldLight;

        digitalWrite(
            Config::PIN_LIGHT,
            lightActive ? HIGH : LOW
        );
        
        if (lightActive)
        {
            std::cout << "ControlManager: Light ON\n";
        }
        else
        {
            std::cout << "ControlManager: Light OFF\n";
        }
    }
}
