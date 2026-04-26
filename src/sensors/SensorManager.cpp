#include "sensors/SensorManager.h"
#include "config/SystemConfig.h"
#include <Arduino.h>


// Constructor
SensorManager::SensorManager()
    : oneWire(Config::PIN_ONEWIRE),
      tempSensor(&oneWire)
{
}


void SensorManager::begin() {
    tempSensor.begin();
}

void SensorManager::update() {
    data.temperature = readTemperature();
    data.conductivity = readTds(data.temperature);
    data.turbidity = readTurbidity();
    data.waterLevel = readWaterLevel();
}

const SensorData& SensorManager::getData() const {
    return data;
}


float SensorManager::readTemperature() {
    tempSensor.requestTemperatures();

    return tempSensor.getTempCByIndex(0);
}

float SensorManager::readTds(float currentTemp) 
{
  int analogVal = analogRead(Config::PIN_TDS);         
  float voltage = analogVal * Config::ADC_REFERENCE_VOLTAGE / Config::ADC_RESOLUTION; // convert to voltage

  float compensationCoefficient = 1.0f + 0.02f * (currentTemp - 25.0);
  float compensationVoltage = voltage / compensationCoefficient;

  return (133.42f * compensationVoltage * compensationVoltage * compensationVoltage 
        - 255.86f * compensationVoltage * compensationVoltage 
        + 857.39f * compensationVoltage) * 0.5f;
}

float SensorManager::readTurbidity() {
    int value = analogRead(Config::PIN_TURBIDITY);

    return ((value * Config::ADC_REFERENCE_VOLTAGE) / Config::ADC_RESOLUTION);
}

int SensorManager::readWaterLevel() {
    digitalWrite(Config::PIN_TRIG, LOW);
    delayMicroseconds(2);
    digitalWrite(Config::PIN_TRIG, HIGH);
    delayMicroseconds(10);
    digitalWrite(Config::PIN_TRIG, LOW);

    float duration = pulseIn(Config::PIN_ECHO, HIGH, 2600);
    float distance = duration / 58.2f;

    constexpr float empty = 19.0f;
    constexpr float safe = 5.0f;

    int level = (int)((empty - distance) / (empty - safe) * 100);

    if (level < 0) level = 0;
    if (level > 100) level = 100;

    return level;
}