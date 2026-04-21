#include <Arduino.h>
#include <EEPROM.h>
#include <string>
#include <Preferences.h>
#include <esp32-hal-log.h>

#include <macros.h>
#include <flash_aw.h>
#include <sensors.h>
#include <base.h>

static const char *AUTOWATER_SENSORS_TAG = "autowater_sensors";

int get_dryness_level(int pin_num /*  = SOIL_INPUT_PIN1 */, int num_retries /*  = 3 */)
{
    int dryness_level = 0;
    for (int i = 0; i < num_retries; i++)
    {
        dryness_level = analogRead(pin_num);
        delay(100);
        ESP_LOGV(AUTOWATER_SENSORS_TAG, "dryness_level#%d: %d", i, dryness_level);
    }
    return dryness_level;
}

long get_required_moist_level()
{
    // required level stored in memory is a number between 0 and 100
    uint8_t moist_setting = getUChar(APPKEY_REQ_MOIST_SETTING, DEFAULT_REQUIRED_MOIST_SETTING);
    return map(moist_setting, 0, 100, DRYNESS_THRESHOLD_LOW, DRYNESS_THRESHOLD_HIGH);
}
