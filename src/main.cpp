#include <Arduino.h>
#include "config/SystemConfig.h"
#include "core/SystemTypes.h"

#include "sensors/SensorManager.h"
#include "storage/SettingsManager.h"
#include "storage/StorageMananger.h"
#include "control/ControlManager.h"
#include "time/RTCManager.h"


// Instantiate manager and settings
SystemSettings settings;

SensorManager sensorManager;
SettingsManager settingsManager;
StorageManager storageManager;
ControlManager controlManager;
RTCManager rtcManager;


// Define timers and intervals
unsigned long lastSensorUpdate = 0;
unsigned long lastControlUpdate = 0;
unsigned long lastLogUpdate = 0;

constexpr unsigned long SENSOR_INTERVAL_MS = 1000;
constexpr unsigned long CONTROL_INTERVAL_MS = 1000;
constexpr unsigned long LOG_INTERVAL_MS = 1000;


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


void setup() 
{
  Serial.begin(115200);

  initializePins();

  settingsManager.begin();
  settingsManager.load(settings);

  storageManager.begin();
  sensorManager.begin();
  rtcManager.begin();

  Serial.println("System initialized");
}


void loop() 
{
  const unsigned long now = millis();

  // Sensor update
  if (now - lastSensorUpdate >= SENSOR_INTERVAL_MS)
  {
    lastSensorUpdate = now;
    sensorManager.update();
  }


  // Control intervall
  if (now - lastControlUpdate >= CONTROL_INTERVAL_MS)
  {
    lastControlUpdate = now;

    controlManager.update(
      sensorManager.getData(),
      settings,
      rtcManager.getHour()
    );
  }


  // Log update
   if (now - lastLogUpdate >= LOG_INTERVAL_MS)
   {
    lastLogUpdate = now;

    const auto& data = sensorManager.getData();

    rtcManager.update();

    storageManager.appendMeasurement(
      data,
      rtcManager.getDate(),
      rtcManager.getTime()
    );

    Serial.printf(
      "T=%.2f Cond=%.2f Turb=%.2f Level=%d\n",
      data.temperature,
      data.conductivity,
      data.turbidity,
      data.waterLevel
    );
   }
}