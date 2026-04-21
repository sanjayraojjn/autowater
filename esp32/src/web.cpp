#include <web.h>

#include <ESPAsyncWebServer.h>
#include <SPIFFS.h>
#include <ArduinoJson.h>
#include <Wifi.h>

#include <sensors.h>
#include <macros.h>
#include <base.h>

extern Led onboard_led;
static const char *AUTOWATER_WEB_TAG = "autowater_web";

AsyncWebServer server(HTTP_PORT);
AsyncWebSocket ws("/ws");

String processor(const String &var)
{
    ESP_LOGI(AUTOWATER_WEB_TAG, "processing variable %s", var);
    return String(var == "STATE" && onboard_led.on ? "on" : "off");
}

void onRootRequest(AsyncWebServerRequest *request)
{
    request->send(SPIFFS, "/index.html", "text/html", false, processor);
    ESP_LOGI(AUTOWATER_WEB_TAG, "new request to webserver");
}

void initWebServer()
{
    server.on("/index.html", onRootRequest);
    server.on("/", onRootRequest);
    server.serveStatic("/", SPIFFS, "/").setDefaultFile("index.html");

    server.on("/srao_autowater", HTTP_GET, [](AsyncWebServerRequest *request)
              {
              const uint8_t doc_size = JSON_OBJECT_SIZE(5);
              StaticJsonDocument<doc_size> esp32_details;

              esp32_details["name"] = WiFi.getHostname();
              esp32_details["device_type"] = "this is an autowater device";
              esp32_details["ip"] = WiFi.localIP().toString();
              esp32_details["mac"] = WiFi.macAddress().c_str();
                //__PL(WiFi.macAddress());

              char json_str[256];
              uint8_t len = serializeJson(esp32_details, json_str);

              request->send(200, "text/json",  json_str); });

    server.on("/sensors", HTTP_GET, [](AsyncWebServerRequest *request)
              {
              const uint8_t doc_size = JSON_OBJECT_SIZE(3);
              StaticJsonDocument<doc_size> readings;

              readings["moist"] = get_dryness_level(SOIL_INPUT_PIN1);
              readings["req_moist"] = get_required_moist_level();

              char json_str[256];
              uint8_t len = serializeJson(readings, json_str);

              request->send(200, "text/json",  json_str); });

    server.begin();
}

void notifyClients(AsyncWebSocket &ws)
{
    const uint8_t doc_size = JSON_OBJECT_SIZE(1);
    StaticJsonDocument<doc_size> json_doc;
    json_doc["status"] = onboard_led.on ? "on" : "off";
    char json_str[128];
    uint8_t len = serializeJson(json_doc, json_str);
    ws.textAll(json_str, len);
}

void send_data(AsyncWebSocketClient *client, char *data)
{
    ws.text(client->id(), data);
}

void handleWebSocketMessage(AsyncWebSocketClient *client, void *args, uint8_t *data, size_t len)
{
    AwsFrameInfo *frame = (AwsFrameInfo *)args;
    // Serial.printf("ws data %d  %d  %d  %d \n", int(frame->final), int(frame->index), int(frame->len), int(len) );
    // Serial.printf("ws data-1 %d  %d \n", int(frame->opcode), int(WS_TEXT) );
    if (frame->final && frame->index == 0 && frame->len == len && frame->opcode == WS_TEXT)
    {
        data[len] = 0;
        // Serial.printf("\n %s %d\n", data, strlen((char*)data) );
        const uint8_t doc_size = JSON_OBJECT_SIZE(1);
        StaticJsonDocument<doc_size> json_doc;
        DeserializationError err = deserializeJson(json_doc, data);
        if (!err)
        {
            if (strcmp(json_doc["action"], "toggle") == 0)
            {
                onboard_led.toggle();
                notifyClients(ws);
            }
            else if (strcmp(json_doc["action"], "get_sensor_params") == 0)
            {
                int dryness_level = get_dryness_level();
                int required_dryness_level = get_required_moist_level();
                const uint8_t doc_size = JSON_OBJECT_SIZE(2);
                StaticJsonDocument<doc_size> json_doc;
                json_doc["dryness_level"] = dryness_level;
                json_doc["required_dryness_level"] = required_dryness_level;
                char json_str[128];
                uint8_t len = serializeJson(json_doc, json_str);
                send_data(client, json_str);
            }
        }
    }
}

//*****************
//* initialize web socket
//*****************
void onEvent(AsyncWebSocket *server,
             AsyncWebSocketClient *client,
             AwsEventType type,
             void *args,
             uint8_t *data,
             size_t len)
{
    // we are going to handle different events defined by the protocol
    switch (type)
    {
    case WS_EVT_CONNECT:
        ESP_LOGI(AUTOWATER_WEB_TAG, "WebSocket client #%u connected from %s", client->id(), client->remoteIP().toString().c_str());
        break;
    case WS_EVT_DISCONNECT:
        ESP_LOGI(AUTOWATER_WEB_TAG, "WebSocket client #%u disconnected", client->id());
        break;
    case WS_EVT_ERROR:
    case WS_EVT_PONG:
        break;
    case WS_EVT_DATA:
        handleWebSocketMessage(client, args, data, len);
        break;
    }
}

void initWebSocket()
{
    ws.onEvent(onEvent);
    server.addHandler(&ws);
}
