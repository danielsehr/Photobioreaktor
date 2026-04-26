#pragma once
#include "core/SystemTypes.h"


class ControlManager {
    public:
        void update(const SensorData& data, const SystemSettings& settings);

    private:
        void controlTemperature(const SensorData& data, const SystemSettings& settings);
        void controlStirring(const SystemSettings& settings);
        void controlLight(const SystemSettings& settings);

        bool stirringActive = false;
        unsigned long stirStartTime = 0;
        unsigned long lastStirTime = 0;
};