#include "DS18B20Driver.h"

DS18B20Driver::DS18B20Driver()
    :oneWire_(Config::PIN_ONEWIRE),
    sensor_(&oneWire_)
{
}


void DS18B20Driver::begin(){
    sensor_.begin();
}


float DS18B20Driver::readTemperature() {
    sensor_.requestTemperatures();

    return sensor_.getTempCByIndex(0);
}