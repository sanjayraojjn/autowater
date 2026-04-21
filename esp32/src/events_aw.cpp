#include <esp32-hal-log.h>
#include <events_aw.h>
#include <esp_err.h>

#include <macros.h>
#include <water.h>

ESP_EVENT_DEFINE_BASE(AUTOWATER_EVENT_BASE);

// initializing instancePtr with NULL
AutoWaterEvents *AutoWaterEvents::instancePtr = NULL;
static const char *AUTOWATER_EVENT_TAG = "autowater_events";

AutoWaterEvents::AutoWaterEvents()
{

    esp_event_loop_args_t evt_loop_args = {
        .queue_size = 5,
        .task_name = "loop_task",
        .task_priority = uxTaskPriorityGet(NULL), /*ignored if name is NULL*/
        .task_stack_size = 3072,                  /*ignored if name is NULLL*/
        .task_core_id = tskNO_AFFINITY,           /*ignored if name is NULL*/
    };

    // create an event loop
    ESP_ERROR_CHECK(esp_event_loop_create(&evt_loop_args, &evt_loop));
    ESP_LOGV(AUTOWATER_EVENT_TAG, "created event loop");

    // register event handler
    ESP_EVENT_DEFINE_BASE(AUTOWATER_EVENT_BASE);

    ESP_ERROR_CHECK(esp_event_handler_register_with(evt_loop, AUTOWATER_EVENT_BASE, AUTOWATER_PLANT_IS_DRY_EVENT, on_plant_is_dry, NULL));
    ESP_LOGV(AUTOWATER_EVENT_TAG, "registered event handler");
}

AutoWaterEvents *AutoWaterEvents::getInstance()
{
    if (instancePtr == NULL)
    {
        instancePtr = new AutoWaterEvents();
    }
    return instancePtr;
}

void AutoWaterEvents::notify(esp_event_base_t evt_base, int32_t evt_id)
{
    ESP_ERROR_CHECK(esp_event_post_to(evt_loop, evt_base, evt_id, NULL, 0, 30000));
}
