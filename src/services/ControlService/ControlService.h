#pragma once
#include "core/SensorData.h"
#include "core/SystemTypes.h"


class ControlService {
    public:
        void update(const SensorData& data, const SystemSettings& settings, int currentHour);

    private:
        void controlTemperature(const SensorData& data, const SystemSettings& settings);
        void controlStirring(const SystemSettings& settings);
        void controlLight(const SystemSettings& settings, int currentHour);

        bool heaterActive = false;
        bool stirringActive = false;
        bool lightActive = false;
        unsigned long stirStartTime = 0;
        unsigned long lastStirTime = 0;
};