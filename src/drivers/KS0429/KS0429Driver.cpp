// https://docs.keyestudio.com/_/downloads/KS0429/en/latest/pdf/
#include "KS0429Driver.h"

namespace
{
    constexpr float ADC_REFERENCE_VOLTAGE = 3.3f;
    constexpr uint16_t ADC_RESOLUTION     = 4095;

    constexpr float REFERENCE_TEMPERATURE = 25.0f;
    constexpr float TEMPERATURE_COEFFICIENT = 0.02f;

    constexpr float TDS_COEFFICIENT_A = 133.42f;
    constexpr float TDS_COEFFICIENT_B = 255.86f;
    constexpr float TDS_COEFFICIENT_C = 857.39f;

    constexpr float TDS_FACTOR = 0.5f;
}


float KS0429Driver::readTds(float currentTemperature) 
{
    int analogValue = analogRead(Config::PIN_TDS);         
  
    float voltage = analogValue * ADC_REFERENCE_VOLTAGE / ADC_RESOLUTION; // convert to voltage

    float compensationCoefficient = 1.0f + TEMPERATURE_COEFFICIENT * (currentTemperature - REFERENCE_TEMPERATURE);
    
    float compensationVoltage = voltage / compensationCoefficient;

    return (
        TDS_COEFFICIENT_A * compensationVoltage * compensationVoltage * compensationVoltage 
        - TDS_COEFFICIENT_B * compensationVoltage * compensationVoltage 
        + TDS_COEFFICIENT_C * compensationVoltage
    ) * TDS_FACTOR;
}