#include <Arduino.h>
#include <esp_timer.h>

#include <macros.h>
#include <power.h>
#include <wifi_aw.h>
#include <spiffs_aw.h>
#include <web.h>

RTC_DATA_ATTR bool pump_was_running = false;

Led onboard_led = {LED_BUILTIN, false};

void setup()
{
    // put your setup code here, to run once:
    pinMode(onboard_led.pin, OUTPUT);

    Serial.begin(9600);
    delay(1000);

    // initWiFi();
    setupWiFi();
    initSPIFFS();
    initWebSocket();
    initWebServer();

    // put your setup code here, to run once:
    // pinMode(SOIL_INPUT_PIN1, INPUT);
    // pinMode(SOIL_INPUT_PIN2, INPUT);
    pinMode(PUMP_CONTROL_PIN, OUTPUT);
    // keep the pump is stopped condition
    digitalWrite(PUMP_CONTROL_PIN, HIGH);
    delay(5000);
}

void loop()
{
    // in deep sleep mode loop method is empty
}
