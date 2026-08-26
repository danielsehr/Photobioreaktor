#pragma once

#include "core/SensorData.h"
#include "storage/StorageManager.h"

class ExperimentService
{
public:
    explicit ExperimentService(StorageManager& storage);

    bool start(const char* name);

    void stop();

    void record(const SensorData& measurement);

    bool isRecording() const;

    const Experiment& currentExperiment() const;

private:
    StorageManager& storageManager_;

    Experiment currentExperiment_{};

    bool recording_ = false;
};