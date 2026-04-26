#pragma once
#include <core/SystemTypes.h>
#include <OneWire.h>
#include <DallasTemperature.h>


class SensorManager{
    public:
        SensorManager();
        
        void begin();
        void update();  // reads all sensors once

        const SensorData& getData() const;

    private:
        SensorData data;

        // Hardware
        OneWire oneWire;
        DallasTemperature tempSensor;

        float readTemperature();
        float readTds(float temp);
        float readTurbidity();
        int readWaterLevel();
};