#include <Arduino.h>
#include "config/SystemConfig.h"
#include "core/SystemTypes.h"

#include "sensors/SensorManager.h"
#include "settings/SettingsManager.h"
#include "storage/StorageMananger.h"
#include "control/ControlManager.h"
#include "time/RTCManager.h"
#include "network/NetworkManager.h"
#include "web/WebSocketManager.h"
#include "web/WebServerManager.h"


// Instantiate manager and settings
SensorManager sensorManager;
SettingsManager settingsManager;
StorageManager storageManager;
ControlManager controlManager;
RTCManager rtcManager;
NetworkManager networkManager;

WebSocketManager webSocketManager(sensorManager);

WebServerManager webServerManager(
  settingsManager,
  sensorManager,
  storageManager, 
  rtcManager,
  webSocketManager
);


// Define timers and intervals
unsigned long lastSensorUpdate = 0;
unsigned long lastControlUpdate = 0;
unsigned long lastLogUpdate = 0;

constexpr unsigned long SENSOR_INTERVAL_MS = 1000;
constexpr unsigned long CONTROL_INTERVAL_MS = 1000;
constexpr unsigned long LOG_INTERVAL_MS = 5000;


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
  storageManager.begin();
  sensorManager.begin();
  rtcManager.begin();
  networkManager.begin();
  webServerManager.begin();

  Serial.println("System initialized");
}


void loop() 
{
  const unsigned long now = millis();

  // SENSOR UPDATE INTERVAL
  if (now - lastSensorUpdate >= SENSOR_INTERVAL_MS)
  {
    lastSensorUpdate = now;
    sensorManager.update();
  }


  // CONTROL INTERVAL
  if (now - lastControlUpdate >= CONTROL_INTERVAL_MS)
  {
    lastControlUpdate = now;

    controlManager.update(
      sensorManager.getData(),
      settingsManager.getSettings(),
      rtcManager.getHour()
    );
  }


  // LOG UPDATE INTERVAL
  if (now - lastLogUpdate >= LOG_INTERVAL_MS)
  {
  lastLogUpdate = now;

  const auto& data = sensorManager.getData();
  
  rtcManager.update();
  const char* date = rtcManager.getDate();
  const char* time = rtcManager.getTime();
  
  // Store data to CSV
  storageManager.appendMeasurement(
    data,
    date,
    time
  );

  
  // Websocket
  webSocketManager.broadcastSensorData();

  // Print data in console
  Serial.printf(
    "[%s %s] T=%.2f°C Cond=%.2f Turb=%.2f Level=%d\n",
    date,
    time,
    data.temperature,
    data.conductivity,
    data.turbidity,
    data.waterLevel
  );
  }
}