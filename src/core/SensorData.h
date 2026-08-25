#pragma once 
#include <Arduino.h>

struct SensorData {
    unsigned long uptimeSeconds = 0;

    float temperature = NAN;
    float conductivity = NAN;
    float turbidity = NAN;
    int waterLevel = -1;
    bool valid;
};