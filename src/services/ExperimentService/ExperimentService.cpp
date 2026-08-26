#include "ExperimentService.h"

ExperimentService::ExperimentService(StorageManager& storageManager)
    : storageManager_(storageManager)
    {
    }

bool ExperimentService::start(const char* name)
{
    if (recording_)
    {
        return false;
    }

    const uint32_t id = storageManager_.nextExperimentId();
    
    if (id == 0)
    {
        return false;
    }
    
    currentExperiment_.id = id;
    
    
    if(name != nullptr &&  name[0] != '\0')
    {
        strncpy(
            currentExperiment_.name,
            name,
            sizeof(currentExperiment_.name) - 1
        );

        currentExperiment_.name[
            sizeof(currentExperiment_.name) - 1
        ] = '\0';
    }
    else
    {
        snprintf(
            currentExperiment_.name,
            sizeof(currentExperiment_.name),
            "experiment_%03lu",
            static_cast<unsigned long>(currentExperiment_.id)
        );
    }

    if (!storageManager_.createExperiment(currentExperiment_))
    {
        return false;
    }

    recording_ = true;

    return true;
}

void ExperimentService::stop()
{
    recording_ = false;
}

void ExperimentService::record(const SensorData& measurement)
{
    if (!recording_)
    {
        return;
    }

    storageManager_.appendMeasurement(
        currentExperiment_, 
        measurement
    );
}

bool ExperimentService::isRecording() const
{
    return recording_;
}

const Experiment& ExperimentService::currentExperiment() const
{
    return currentExperiment_;
}
