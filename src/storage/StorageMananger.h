#pragma once
#include "core/SensorData.h"

class StorageManager{
    public:
        bool begin();
        bool appendMeasurement(const SensorData& data,
                               const char* date,
                               const char* time);
    private:
        bool createCsvIfMissing();
};