#ifndef __AUTOWATER_WEB_H__
#define __AUTOWATER_WEB_H__

#include <ESPAsyncWebServer.h>
#include <SPIFFS.h>
#include <ArduinoJson.h>
#include <Wifi.h>

String processor(const String &var);

void onRootRequest(AsyncWebServerRequest *request);

void initWebServer();

void notifyClients(AsyncWebSocket &ws);

void send_data(AsyncWebSocketClient *client, char *data);

void handleWebSocketMessage(AsyncWebSocketClient *client, void *args, uint8_t *data, size_t len);

//*****************
//* initialize web socket
//*****************
void onEvent(AsyncWebSocket *server,
             AsyncWebSocketClient *client,
             AwsEventType type,
             void *args,
             uint8_t *data,
             size_t len);

void initWebSocket();

#endif //__AUTOWATER_WEB_H__
