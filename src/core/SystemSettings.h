#pragma once 
#include <Arduino.h>

struct SystemSettings {
    int maxTemp = 30;
    int minTemp = 30;
    int stirIntervalMinutes = 1;
    int stirDurationMinutes = 1;
    int lightOnHour = 0;
    int lightOffHour = 24;
    int measurementIntervalSeconds = 1;
};

inline constexpr SystemSettings DEFAULT_SETTINGS{};