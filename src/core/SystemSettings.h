#pragma once 
#include <Arduino.h>

struct SystemSettings {
    int maximalTemperatureCelcius = 30;
    int minimalTemperatureCelcius = 30;
    int stirringIntervalMinutes = 1;
    int stirringDurationMinutes = 1;
    int lightOnHour = 0;
    int lightOffHour = 24;
    int measurementIntervalSeconds = 1;
};

inline constexpr SystemSettings DEFAULT_SETTINGS{};