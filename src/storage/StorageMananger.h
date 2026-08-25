#pragma once
#include "core/SystemTypes.h"

class StorageManager{
    public:
        bool begin();
        bool appendMeasurement(const SensorData& data,
                               const char* date,
                               const char* time);
    private:
        bool createCsvIfMissing();
};