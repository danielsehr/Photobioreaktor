// #pragma once
#include "settings/SettingsManager.h"


bool SettingsManager::begin() {
    return preferences.begin(NAMESPACE_NAME, false);
}


bool SettingsManager::load(SystemSettings& settings) {
    settings.maxTemp = preferences.getInt("MaxTemp", DEFAULT_SETTINGS.maxTemp);
    settings.minTemp = preferences.getInt("MinTemp", DEFAULT_SETTINGS.minTemp);
    settings.stirIntervalMinutes = preferences.getInt("StirrInt", DEFAULT_SETTINGS.stirIntervalMinutes);
    settings.stirDurationMinutes = preferences.getInt("StirrDur", DEFAULT_SETTINGS.stirDurationMinutes);
    settings.lightOnHour = preferences.getInt("LightOn", DEFAULT_SETTINGS.lightOnHour);
    settings.lightOffHour = preferences.getInt("LightOff", DEFAULT_SETTINGS.lightOffHour);
    settings.measurementIntervalSeconds = preferences.getInt("MeasInt", DEFAULT_SETTINGS.measurementIntervalSeconds);

    return true;
}


bool SettingsManager::save(const SystemSettings& settings) {
    preferences.putInt("MaxTemp", settings.maxTemp);
    preferences.putInt("MinTemp", settings.minTemp);
    preferences.putInt("StirrInt", settings.stirIntervalMinutes);
    preferences.putInt("StirrDur", settings.stirDurationMinutes);
    preferences.putInt("LightOn", settings.lightOnHour);
    preferences.putInt("LightOff", settings.lightOffHour);
    preferences.putInt("MeasInt", settings.measurementIntervalSeconds);

    return true;
}


bool SettingsManager::reset(SystemSettings& settings) {
    preferences.clear();
    
    settings = DEFAULT_SETTINGS;
    
    return save(settings);
}