#include "DS18B20Driver.h"
#include "utils/logger/Logger.h"

DS18B20Driver::DS18B20Driver()
    :oneWire_(Config::PIN_ONEWIRE),
    sensor_(&oneWire_)
{
}


void DS18B20Driver::begin(){

    sensor_.begin();

    if(sensor_.getDeviceCount() == 0)
    {
        LOG_INFO("[DS18B20 Driver] No temperature sensor found!");
        return;
    } 
    else 
    {
        LOG_INFO("[DS18B20 Driver] %d sensor found!", sensor_.getDeviceCount());
    }
}


float DS18B20Driver::readTemperature() {
    sensor_.requestTemperatures();

    return sensor_.getTempCByIndex(0);
}