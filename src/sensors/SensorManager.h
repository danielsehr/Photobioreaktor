#pragma once
#include <OneWire.h>
#include <DallasTemperature.h>
#include "core/SensorData.h"


class SensorManager{
    public:
        SensorManager();
        
        void begin();
        void update();  // reads all sensors once

        const SensorData& getData() const;

    private:
        SensorData data;
        OneWire oneWire;
        DallasTemperature tempSensor;

        float readTemperature();
        float readTds(float temp);
        float readTurbidity();
        int readWaterLevel();
};