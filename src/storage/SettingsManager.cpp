#pragma once
# include "storage/SettingsManager.h"

bool SettingsManager::begin() {
    return preferences.begin(NAMESPACE_NAME, false);
}

bool SettingsManager::load(SystemSettings& settings) {
    settings.maxTemp = preferences.getInt("MaxTemp", 30);
    settings.minTemp = preferences.getInt("MinTemp", 20);
    settings.stirIntervalMinutes = preferences.getInt("StirrInt", 30);
    settings.stirDurationMinutes = preferences.getInt("StirrDur", 1);
    settings.lightOnHour = preferences.getInt("LightOn", 8);
    settings.lightOffHour = preferences.getInt("LightOff", 20);
    settings.measurementIntervalSeconds = preferences.getInt("MeasInt", 1);

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