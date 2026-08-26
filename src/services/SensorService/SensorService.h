#pragma once
#include "core/SensorData.h"
#include "drivers/DS18B20/DS18B20Driver.h"
#include "drivers/HCSR04/HCSR04Driver.h"
#include "drivers/KS0429/KS0429Driver.h"

class SensorService{
    public:
        void begin();

        void initializePins();

        void update();

        const SensorData& latestMeasurement() const;

        bool hasNewMeasurement() const;

        void clearNewMeasurement();

    private:
        DS18B20Driver DS18B20Driver_;

        HCSR04Driver HCSR04Driver_;

        KS0429Driver KS0429Driver_;

        SensorData latest_;

        uint32_t lastRead_ = 0;

        bool newMeasurement_ = false;
};