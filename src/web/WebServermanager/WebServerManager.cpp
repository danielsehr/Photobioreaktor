#include <ArduinoJson.h>
#include <LittleFS.h>
#include "web/WebServerManager/WebServerManager.h"


// Creates construct. parameters, binds them to adress reference i pass in
WebServerManager::WebServerManager(
    SettingsManager& settingsMgr,
    SensorService& sensorMgr,
    StorageManager& storageMgr,
    RTCManager& rtcMgr,
    WebSocketManager& webSocketMgr)
    : settingsManager(settingsMgr),
      sensorService(sensorMgr),
      storageManager(storageMgr),
      rtcManager(rtcMgr),
      webSocketManager(webSocketMgr) 
    {}


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



