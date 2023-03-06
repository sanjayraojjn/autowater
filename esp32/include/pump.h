#ifndef __AUTOWATER_PUMP_H__
#define __AUTOWATER_PUMP_H__

#include <Arduino.h>

#include <macros.h>
#include <base.h>

void run_pump_aw(int duration_in_ms = MAX_IRRIGATION_TIME_mS)
{
    // set the pin high
    digitalWrite(PUMP_CONTROL_PIN, LOW);
    // record time and flag
    __PL("Pump has started for " + String(duration_in_ms) + " milli seconds");
    Serial.flush();
    int duration_in_sec = duration_in_ms / S_TO_mS_FACTOR;
    for (int i = 0; i < duration_in_sec; i++)
    {
        delay(1000);
    }
    // set the pin low
    digitalWrite(PUMP_CONTROL_PIN, HIGH);
    // pump is stopped
    __PL("Pump is stopped");
}

#endif //__AUTOWATER_PUMP_H__
