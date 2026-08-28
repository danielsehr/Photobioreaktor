#include "utils/logger/Logger.h"
#include "settings/SettingsManager.h"

bool SettingsManager::begin() 
{
    return load();
}

bool SettingsManager::load() {
    if (!preferences_.begin("settings", true))
    {
        LOG_ERROR("[SettingsManager] Failed opening preferences.");
        return false;
    }
    
    settings_.maximalTemperatureCelcius = preferences_.getInt(
        "maximalTemperatureCelcius", 
        DEFAULT_SETTINGS.maximalTemperatureCelcius
    );

    settings_.minimalTemperatureCelcius = preferences_.getInt(
        "minimalTemperatureCelcius", 
        DEFAULT_SETTINGS.minimalTemperatureCelcius
    );
    
    settings_.stirringIntervalMinutes = preferences_.getInt(
        "stirringIntervalMinutes", 
        DEFAULT_SETTINGS.stirringIntervalMinutes
    );
   
    settings_.stirringDurationMinutes = preferences_.getInt(
        "stirringDurationMinutes", 
        DEFAULT_SETTINGS.stirringDurationMinutes
    );
    
    settings_.lightOnHour = preferences_.getInt(
        "lightOnHour", 
        DEFAULT_SETTINGS.lightOnHour
    );
    
    settings_.lightOffHour = preferences_.getInt(
        "lightOffHour", 
        DEFAULT_SETTINGS.lightOffHour
    );
    
    settings_.measurementIntervalSeconds = preferences_.getInt(
        "measurementIntervalSeconds", 
        DEFAULT_SETTINGS.measurementIntervalSeconds
    );

    preferences_.end();
    
    return true;
}

bool SettingsManager::update(const SystemSettings& newSettings) {
    
    if (!preferences_.begin("settings", true))
    {
        LOG_ERROR("[SettingsManager] Failed opening preferences.");
        return false;
    }
    
    preferences_.putInt("MaxTemp", newSettings.maximalTemperatureCelcius);

    preferences_.putInt("MinTemp", newSettings.minimalTemperatureCelcius);

    preferences_.putInt("StirrInt", newSettings.stirringIntervalMinutes);

    preferences_.putInt("StirrDur", newSettings.stirringDurationMinutes);

    preferences_.putInt("LightOn", newSettings.lightOnHour);

    preferences_.putInt("LightOff", newSettings.lightOffHour);

    preferences_.putInt("MeasInt", newSettings.measurementIntervalSeconds);
    
    preferences_.end();
    
    settings_ = newSettings;

    return true;
}

const SystemSettings& SettingsManager::getSettings() const
{
    return settings_;
}

bool SettingsManager::reset() 
{
    settings_ = DEFAULT_SETTINGS;
    
    return update(settings_);
}