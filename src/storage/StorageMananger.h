#pragma once
#include <LittleFS.h>
#include "core/Experiment.h"
#include "core/SensorData.h"

class StorageManager
{
public:
    void begin();

    bool createExperiment(const Experiment& experiment);

    bool appendMeasurement(const Experiment experiment, const SensorData& measurement);

    bool finishExperiment(const Experiment& experiment);

    bool createCsvPath(const Experiment& experiment, char* buffer) const;
    
    uint32_t nextExperimentId() const;

    void listDirectory(const char* path);

    std::size_t listExperimentIds(uint32_t* ids, std::size_t capacity) const;

private:
    void initializeFileSystem();

    void serializeMeasurementCsv(File& file, const SensorData& measurement);
};