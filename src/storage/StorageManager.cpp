#include "storage/StorageManager.h"
#include "config/SystemConfig.h"
#include "utils/logger/Logger.h"

void StorageManager::begin() {
    initializeFileSystem();
}


void StorageManager::initializeFileSystem()
{
    if (!LittleFS.begin(true))
    {
        LOG_ERROR("Failed to mount LittleFS.");
        return;
    }

    if (!LittleFS.exists("/experiments"))
    {
        if (!LittleFS.mkdir("/experiments"))
        {
            LOG_ERROR("Failed to create experiments directory.");
            return;
        }
    }

    LOG_INFO("LittleFS mounted.");
}


bool StorageManager::createExperiment(const Experiment& experiment) 
{
    char path[Config::CSV_PATH_MAX];

    if(!createCsvPath(experiment, path))
    {
        return false;
    }

    File file = LittleFS.open(path, FILE_WRITE);

    if (!file)
    {
        // LOG_ERROR("Could not open csv file: %s", path);
        return false;
    }

    file.println("timestamp, temperature, conductivity, turbidity, waterlevel");

    file.close();

    return true;
}

bool StorageManager::appendMeasurement(
    const Experiment experiment, 
    const SensorData& measurement)
{
    char path[Config::CSV_PATH_MAX];

    if(!createCsvPath(experiment, path))
    {
        return false;
    }

    File file = LittleFS.open(path, FILE_APPEND);

    if (!file)
    {
        LOG_ERROR("Failed to open csv file.");
        return false;
    }

    if (file.size() == 0)
    {
        file.println("timestamp, temperature_celcius, humidity_percent, valid");
    }

    serializeMeasurementCsv(file, measurement);

    file.close();

    LOG_INFO("Wrote measurement to csv.");

    return true;
}

bool StorageManager::createCsvPath(const Experiment& experiment, char* buffer) const
{
    const int written = snprintf(
        buffer,
        Config::CSV_PATH_MAX,
        Config::HISTORY_FILE_TEMPLATE,
        static_cast<unsigned long>(experiment.id)
    );

    if (written < 0 || static_cast<size_t>(written) >= Config::CSV_PATH_MAX)
    {
        LOG_ERROR("Failed to create CSV path.");
        return false;
    }

    return true;
}


uint32_t StorageManager::nextExperimentId() const 
{
    uint32_t id = 1;
    
    char path[Config::CSV_PATH_MAX];

    while (true)
    {
        Experiment experiment;
        experiment.id = id;

        if(!createCsvPath(experiment, path))
        {
            return 0;
        }

        if (!LittleFS.exists(path))
        {
            return id;
        }

        ++id;
    }
}


void StorageManager::listDirectory(const char* path)
{
    File directory = LittleFS.open(path);

    if (!directory || !directory.isDirectory())
    {
        LOG_ERROR("Failed to open directory: %s", path);
        return;
    }

    File file = directory.openNextFile();

    while (file)
    {
        LOG_INFO(
            "%s (%lu bytes)",
            file.name(),
            static_cast<unsigned long>(file.size())
        );

        file = directory.openNextFile();
    }
}


std::size_t StorageManager::listExperimentIds(uint32_t* ids, std::size_t capacity) const
{
    File directory = LittleFS.open("/experiments");

    if(!directory || !directory.isDirectory())
    {
        LOG_ERROR("Failed to open experiments directory");
        return 0;
    }

    
    std::size_t count = 0;

    File file = directory.openNextFile();

    while (file && count < capacity)
    {
        const char* name = file.name();

        unsigned long id;

        if (sscanf(name, "exp%lu.csv", &id) == 1)
        {
            ids[count] = static_cast<uint32_t>(id);
            ++count;
        }

        file = directory.openNextFile();
    }

    return count;
}


void StorageManager::serializeMeasurementCsv(File& file, const SensorData& measurement)
{
    file.print(measurement.uptimeSeconds);
    file.print(',');
    
    file.print(measurement.temperature);
    file.print(',');
    
    file.print(measurement.conductivity);
    file.print(',');
    
    file.print(measurement.turbidity);
    file.print(',');
    
    file.println(measurement.waterLevel);

    // file.printf(
    //     "%lu,%.2f,%.2f\n",
    //     static_cast<unsigned long>(measurement.timestamp),
    //     measurement.temperatureCelcius,
    //     measurement.humidityPercent
    // );
}