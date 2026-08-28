#include "config/SystemConfig.h"
#include "ActuatorService.h"

void ActuatorService::setHeater(bool active)
{
    digitalWrite(Config::PIN_HEATER, active ? HIGH : LOW);
}

void ActuatorService::setStirrer(bool active)
{
    digitalWrite(Config::PIN_STIRRER, active ? HIGH : LOW);
}

void ActuatorService::setLigth(bool active)
{
    digitalWrite(Config::PIN_LIGHT, active ? HIGH : LOW);
}