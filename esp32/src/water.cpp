// global imports
#include <Arduino.h>

#include <string>

// private imports
#include <macros.h>
#include <sensors.h>
#include <water.h>
#include <pump.h>
#include <base.h>

void AutoWaterCheck::operator()()
{
    static bool event_plant_dry_raised = false;
    // check soil moisture level
    int dryness_level = get_dryness_level();
    __PL("current dryness level: " + String(dryness_level));
    // check required moist settings
    int moist_setting = get_required_moist_level();
    int required_dryness_level = map(moist_setting, 0, 100, DRYNESS_THRESHOLD_HIGH, DRYNESS_THRESHOLD_LOW);
    __PL("required dryness level: " + String(required_dryness_level));

    // it will raise dry plant event again if dryness level is above offset, OR dryness level is above required_level and last time it raised the event
    if ((dryness_level > (required_dryness_level + DRYNESS_OFFSET)) ||
        ((dryness_level > required_dryness_level) && (event_plant_dry_raised)))
    {
        event_plant_dry_raised = true;
        // in this case PLANT_IS_DRY event should be raised

        // TODO: TODO: TODO:OOOOOOOOOO
    }
    else
    {
        __PL("Soil is OK. long sleep");
        event_plant_dry_raised = false;
    }
}

void AutoWater::operator()()
{
    // PUMP needs to be started if it is too dry or
    // during last cycle pump was running and required level was not achieved
    // check soil moisture level
    int dryness_level = get_dryness_level();
    __PL("current dryness level: " + String(dryness_level));
    // check required moist settings
    int moist_setting = get_required_moist_level();
    int required_dryness_level = map(moist_setting, 0, 100, DRYNESS_THRESHOLD_HIGH, DRYNESS_THRESHOLD_LOW);
    __PL("required dryness level: " + String(required_dryness_level));

    // we should double check before starting pump
    if (dryness_level > (required_dryness_level + DRYNESS_OFFSET))
    {

        // TODO: TODO: TODO:OOOOOOOOOO, probably it should raise an event to start a pump
        __PL("Soil is dry. Pump is starting");
        run_pump_aw();
    }
}
