#pragma once
#include <OneWire.h>
#include <DallasTemperature.h>
#include "config/SystemConfig.h"
#include "core/SensorData.h"

class DS18B20Driver
{
public:
    DS18B20Driver();
    
    void begin();
    
    float readTemperature();
    
private:
    OneWire oneWire_;
    DallasTemperature sensor_;
};