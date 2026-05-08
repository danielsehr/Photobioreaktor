#pragma once 
#include <Arduino.h>


struct SensorData {
    unsigned long uptimeSeconds = 0;

    float temperature = NAN;
    float conductivity = NAN;
    float turbidity = NAN;
    int waterLevel = -1;
};

struct SystemSettings {
    int maxTemp = 30;
    int minTemp = 30;
    int stirIntervalMinutes = 1;
    int stirDurationMinutes = 1;
    int lightOnHour = 8;
    int lightOffHour = 24;
    int measurementIntervalSeconds = 1;
};

inline constexpr SystemSettings DEFAULT_SETTINGS{};


