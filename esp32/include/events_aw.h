#ifndef __AUTOWATER_EVENTS_H__
#define __AUTOWATER_EVENTS_H__

#include <esp32-hal-log.h>
#include <esp_event.h>

ESP_EVENT_DECLARE_BASE(AUTOWATER_EVENT_BASE);

enum
{
    AUTOWATER_PLANT_IS_DRY_EVENT,
};

class AutoWaterEvents
{
private:
    static AutoWaterEvents *instancePtr;
    esp_event_loop_handle_t evt_loop;

private:
    AutoWaterEvents();
    // void on_plant_is_dry(void *evt_loop, esp_event_base_t evt_base, int32_t evt_id, void *evt_data);

public:
    AutoWaterEvents(AutoWaterEvents &obj) = delete;
    static AutoWaterEvents *getInstance();

    void notify(esp_event_base_t evt_base, int32_t evt_id);
};

#endif //__AUTOWATER_EVENTS_H__