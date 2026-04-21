// global imports
#include <Arduino.h>
#include <esp_err.h>
#include <esp_event.h>

#include <string>

// private imports
#include <macros.h>
#include <sensors.h>
#include <water.h>
#include <base.h>
#include <events_aw.h>
#include <esp32-hal-log.h>

static const char *AUTOWATER_WATER_TAG = "autowater_water";

void check_water()
{
    AutoWaterCheck check;
    check();
}

void water_plant()
{
    AutoWater water;
    water();
}

extern Led onboard_led;

void on_plant_is_dry(void *evt_loop, esp_event_base_t evt_base, int32_t evt_id, void *evt_data)
{
    /*
    @param evt_loop - name of the loop to which this handler will be registered
    @param evt_base - base event class to which this handler will be registered
    @param evt_id - event id for which this handler will be registered
    @param evt_data - data associated with event to be handled
    */
    ESP_LOGV(AUTOWATER_WATER_TAG, "on_plant_is_dry");
    onboard_led.toggle();

    water_plant();
}

void AutoWaterCheck::operator()()
{
    static bool event_plant_dry_raised = false;
    // check soil moisture level
    int dryness_level = get_dryness_level();
    ESP_LOGD(AUTOWATER_WATER_TAG, "current dryness level: %d", dryness_level);
    // check required moist settings
    int required_dryness_level = get_required_moist_level();
    ESP_LOGD(AUTOWATER_WATER_TAG, "required dryness level: %d", required_dryness_level);

    // it will raise dry plant event again if dryness level is above offset, OR dryness level is above required_level and last time it raised the event
    if ((dryness_level > (required_dryness_level + DRYNESS_OFFSET)) ||
        ((dryness_level > required_dryness_level) && (event_plant_dry_raised)))
    {
        // in this case PLANT_IS_DRY event should be raised
        AutoWaterEvents::getInstance()->notify(AUTOWATER_EVENT_BASE, AUTOWATER_PLANT_IS_DRY_EVENT);
        event_plant_dry_raised = true;
    }
    else
    {
        ESP_LOGD(AUTOWATER_WATER_TAG, "Soil is OK. long sleep");
        event_plant_dry_raised = false;
    }
}

void AutoWater::run_pump_aw(int duration_in_ms /*  = MAX_IRRIGATION_TIME_mS */)
{
    // set the pin high
    digitalWrite(PUMP_CONTROL_PIN, LOW);
    // record time and flag
    ESP_LOGI(AUTOWATER_WATER_TAG, "Pump has started for %d milli seconds", duration_in_ms);
    Serial.flush();
    int duration_in_sec = duration_in_ms / S_TO_mS_FACTOR;
    for (int i = 0; i < duration_in_sec; i++)
    {
        delay(1000);
    }
    // set the pin low
    digitalWrite(PUMP_CONTROL_PIN, HIGH);
    // pump is stopped
    ESP_LOGI(AUTOWATER_WATER_TAG, "Pump is stopped");
}

void AutoWater::operator()()
{
    // PUMP needs to be started if it is too dry or
    // during last cycle pump was running and required level was not achieved
    // check soil moisture level
    int dryness_level = get_dryness_level();

    ESP_LOGI(AUTOWATER_WATER_TAG, "just before starting water, current dryness level: %s", String(dryness_level));
    // check required moist settings
    int required_dryness_level = get_required_moist_level();
    ESP_LOGI(AUTOWATER_WATER_TAG, "required dryness level: %d", required_dryness_level);

    // we should double check before starting pump
    if (dryness_level > (required_dryness_level + DRYNESS_OFFSET))
    {
        ESP_LOGI(AUTOWATER_WATER_TAG, "Soil is dry. Pump is starting");
        this->run_pump_aw();
    }
}
