#include <iostream>
#include "config/SystemConfig.h"
#include "utils/logger/Logger.h"
#include "services/ControlService/ControlService.h"

void ControlService::update(
    const SensorData& data,
    const SystemSettings& settings,
    int currentHour
    )
{
    controlTemperature(data, settings);
    controlStirring(settings);
    controlLight(settings, currentHour);
}


void ControlService::controlTemperature(const SensorData& data, const SystemSettings& settings) {
    const bool waterOk  = 
        data.waterLevel > Config::MIN_WATER_LEVEL;

    const bool tempValid = 
        data.temperature > 0;

    bool shouldHeat = false;

    if (waterOk && tempValid)
    {
        if (data.temperature < settings.minimalTemperatureCelcius)
        {
            shouldHeat = true;
        }
        else if (data.temperature > settings.maximalTemperatureCelcius)
        {
            shouldHeat = false;
        }
        else
        {
            shouldHeat = heaterActive_;
        }
    }
    else
    {
        LOG_INFO("[ControlService] Invalid water level or temperature!\n");
        shouldHeat = false;
    }

    
    if (shouldHeat != heaterActive_)
    {
        heaterActive_ = shouldHeat;
        
        actuatorService_.setHeater(heaterActive_);

        LOG_INFO(
            heaterActive_
                ? "[ControlService] Heater ON"
                : "[ControlService] Heater OFF"
        );
    }
}


void ControlService::controlStirring(const SystemSettings& settings) {
    const unsigned long stirIntervalMs =
        static_cast<unsigned long>(settings.stirringIntervalMinutes) * Config::MS_PER_MINUTE;
    
    const unsigned long stirDurationMs =
        static_cast<unsigned long>(settings.stirringDurationMinutes) * Config::MS_PER_MINUTE;

    unsigned long now = millis();

    bool shouldStir = stirringActive_;

    if (!stirringActive_ && now - lastStirTime_ >= stirIntervalMs)
    {
        shouldStir = true;
        stirStartTime_ = now;
    }
    
    if (stirringActive_ && now - stirStartTime_ >= stirDurationMs)
    {
        shouldStir = false;
        lastStirTime_ = now;
    }

    if (shouldStir != stirringActive_) 
    {
        stirringActive_ = shouldStir;

        actuatorService_.setStirrer(stirringActive_);
        
        LOG_INFO(
            stirringActive_
                ? "[ControlService] Stirring ON\n"
                : "[ControlService] Stirring OFF\n"
        );
    }
}


void ControlService::controlLight(const SystemSettings& settings, int currentHour) {

    bool shouldLight = lightActive_;
    
    if (currentHour >= settings.lightOnHour && currentHour < settings.lightOffHour)
    {
        shouldLight = true;
    }
    else 
    {
        shouldLight = false;
    } 

    if (shouldLight != lightActive_) 
    {
        lightActive_ = shouldLight;

        actuatorService_.setLight(lightActive_);
        
        LOG_INFO(
            lightActive_
                ? "[ControlService] Light ON\n"
                : "[ControlService] Light OFF\n"
        );
    }
}