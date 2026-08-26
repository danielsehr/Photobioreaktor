#include <Arduino.h>
#include "services/SensorService/SensorService.h"
#include "config/SystemConfig.h"
#include "utils/logger/Logger.h"

void SensorService::begin(){
    initializePins();
    LOG_INFO("Sensor service initialized.");
}


void SensorService::initializePins() {
  pinMode(Config::PIN_HEATER, OUTPUT);
  pinMode(Config::PIN_STIRRER, OUTPUT);
  pinMode(Config::PIN_LIGHT, OUTPUT);
  pinMode(Config::PIN_STATUS_LED, OUTPUT);

  pinMode(Config::PIN_RESET, INPUT_PULLUP);

  pinMode(Config::PIN_TDS, INPUT);
  pinMode(Config::PIN_TURBIDITY, INPUT);

  pinMode(Config::PIN_TRIG, OUTPUT);
  pinMode(Config::PIN_ECHO, INPUT);
}


void SensorService::update()
{
    const unsigned long now = millis();
    
    if (now - lastRead_ < Config::SENSOR_UPDATE_MS)
        return;

    lastRead_ = now;

    SensorData data{};

    data.temperature = DS18B20Driver_.readTemperature();
    data.conductivity = KS0429Driver_.readTds(data.temperature);
    data.turbidity = 0;
    data.waterLevel = HCSR04Driver_.readWaterLevel();

    // This needs to put in the driver
    // if (!measurement.valid)
    // {
    //     LOG_WARNING("Invalid sensor reading.");

    //     return;
    // }

    latest_ = data;

    newMeasurement_ = true;

    LOG_INFO("Sensor updated.\n");
    Logger::info(latest_);
}


const SensorData& SensorService::latestMeasurement() const
{
    return latest_;
}


bool SensorService::hasNewMeasurement() const
{
    return newMeasurement_;
}


void SensorService::clearNewMeasurement()
{
    newMeasurement_ = false;
}
