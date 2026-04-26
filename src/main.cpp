#include <Arduino.h>
#include "config/SystemConfig.h"
#include "core/SystemTypes.h"


// Functions
void initializePins() {
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

void setup() {
  Serial.begin(115200);
  initializePins();
  
}

void loop() {

}