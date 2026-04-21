#include <Arduino.h>
#include <Ticker.h>

#include <macros.h>
#include <power.h>
#include <wifi_aw.h>
#include <spiffs_aw.h>
#include <web.h>
#include <water.h>

RTC_DATA_ATTR bool pump_was_running = false;

Led onboard_led = {LED_BUILTIN, false};
Ticker periodic_timer;

void setup()
{
    // put your setup code here, to run once:
    pinMode(onboard_led.pin, OUTPUT);

    Serial.begin(115200);
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

    // now start watering program
    periodic_timer.attach_ms(DEEP_SLEEP_TIME_mS, check_water);
}

void loop()
{
    // in deep sleep mode loop method is empty
}
