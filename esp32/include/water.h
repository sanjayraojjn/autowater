#ifndef __AUTOWATER_WATER_H__
#define __AUTOWATER_WATER_H__

class AutoWaterCheck
{
private:
public:
    void operator()();
};

void check_water();

class AutoWater
{
private:
    void run_pump_aw(int duration_in_ms = MAX_IRRIGATION_TIME_mS);

public:
    void operator()();
};

void water_plant();
void on_plant_is_dry(void *evt_loop, esp_event_base_t evt_base, int32_t evt_id, void *evt_data);

#endif //__AUTOWATER_WATER_H__