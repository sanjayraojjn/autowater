#include <Arduino.h>
#include <EEPROM.h>
#include <string>
#include <Preferences.h>

#include <macros.h>
#include <flash_aw.h>
#include <sensors.h>
#include <base.h>

int get_dryness_level(int pin_num /*  = SOIL_INPUT_PIN1 */, int num_retries /*  = 3 */)
{
    int dryness_level = 0;
    for (int i = 0; i < num_retries; i++)
    {
        dryness_level = analogRead(pin_num);
        delay(100);
        __PL(("dryness_level#" + String(i) + ": " + String(dryness_level)));
    }
    return dryness_level;
}

long get_required_moist_level()
{
    // required level stored in memory is a number between 0 and 100
    uint8_t req_level = getUChar(APPKEY_REQ_MOIST);
    return map(req_level, 0, 100, DRYNESS_THRESHOLD_LOW, DRYNESS_THRESHOLD_HIGH);
}
