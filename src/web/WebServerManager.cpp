#include "web/WebServerManager.h"

#include <ArduinoJson.h>
#include <LittleFS.h>


// Creates construct. parameters, binds them to adress reference i pass in
WebServerManager::WebServerManager(
    SettingsManager& settingsMgr,
    SensorManager& sensorMgr,
    StorageManager& storageMgr,
    RTCManager& rtcMgr,
    WebSocketManager& webSocketMgr)
    : settingsManager(settingsMgr),
      sensorManager(sensorMgr),
      storageManager(storageMgr),
      rtcManager(rtcMgr),
      webSocketManager(webSocketMgr) 
{
}


void WebServerManager::begin(){
    setupRoutes();

    webSocketManager.begin(server);

    server.begin();
}


void WebServerManager::setupRoutes()
{
    server.on("/", HTTP_GET, [](AsyncWebServerRequest* request)
    {
        request->send(
            LittleFS,
            "/index.html",
            "text/html"
        );
    });
    
    server.serveStatic("/", LittleFS, "/");
}



