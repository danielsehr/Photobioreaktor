#pragma once
#include "config/SystemConfig.h"
#include "drivers/DS18B20/DS18B20Driver.h"

class KS0429Driver
{
public:
    float readTds(float currentTemperature);

private:
};