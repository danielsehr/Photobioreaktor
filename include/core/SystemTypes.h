// #pragma once // still not sure if we need this
# include <Arduino.h>


struct SensorData {
    float temperature = NAN;
    float conductivity = NAN;
    float turbidity = NAN;
    int waterLevel = -1;
    uint32_t uptimeSeconds = 0;
};

struct SystemDefaultSettings {
    int maxTemp = 30;
    int minTemp = 20;
    int stirIntervalMinutes = 30;
    int stirDurationMinutes = 1;
    int lightOnHout = 8;
    int lightOffHour = 20;
    int measurementIntervalSeconds = 1;
};


