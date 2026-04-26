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
    int minTemp = 20;
    int stirIntervalMinutes = 30;
    int stirDurationMinutes = 1;
    int lightOnHour = 8;
    int lightOffHour = 20;
    int measurementIntervalSeconds = 1;
};

inline constexpr SystemSettings DEFAULT_SETTINGS{};


