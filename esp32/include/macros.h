#ifndef __AUTOWATER_MACRO_H__
#define __AUTOWATER_MACRO_H__

#define S_TO_uS_FACTOR 1000000
#define S_TO_mS_FACTOR 1000
#define mS_TO_uS_FACTOR 1000

#define PUMP_CONTROL_PIN 14
#define SOIL_INPUT_PIN1 33
#define SOIL_INPUT_PIN2 32
#define POTENTIOMETER_PIN 35

// #define DEV_FLAG 1

#define DRYNESS_THRESHOLD_HIGH 2800
#define DRYNESS_THRESHOLD_LOW 1200
#define DRYNESS_LEVELS 4096
#define DRYNESS_OFFSET 200
#define DEFAULT_REQUIRED_MOIST 1600

// time intervals

// define some global names
#define APPNAME "AUTOWATER"
#define APPKEY_REQ_MOIST "REQ_MOIST"

// web parameters
#define HTTP_PORT 80

// in development environment
#ifdef DEV_FLAG

// initial warmup time 60 seconds
#define WARMUP_S 60

// deep sleep time 30 seconds
#define DEEP_SLEEP_TIME 30
// 30 seconds or 0.5 minutes
#define LONG_DELAY_S 30
// 6 seconds
#define SHORT_DELAY_S 6
// 1 second
#define MICRO_DELAY_S 1

#else // DEV_FLAG

// initial warmup time 600 seconds or 10 minutes
#define WARMUP_S 600

// deep sleep time 1800 seconds or 30 minutes
#define DEEP_SLEEP_TIME 1800
// 300 seconds or 5 minutes
#define LONG_DELAY_S 300
// 60 seconds or 1 minutes
#define SHORT_DELAY_S 60
// 10 seconds
#define MICRO_DELAY_S 10

#endif // DEV_FLAG
// 30 seonds
#define SHORT_HALF_DELAY_S 30

#define DEEP_SLEEP_TIME_mS (DEEP_SLEEP_TIME * S_TO_mS_FACTOR)
#define LONG_DELAY_mS (LONG_DELAY_S * S_TO_mS_FACTOR)
#define PUMP_REST_TIME_mS (LONG_DELAY_mS)
#define PUMP_REST_TIME_uS (LONG_DELAY_S * S_TO_uS_FACTOR)
#define PUMP_REST_TIME_S LONG_DELAY_S
#define SENSOR_CHECK_INTERVAL_mS (LONG_DELAY_S * S_TO_mS_FACTOR)
#define PUMP_RUNNING_CHECK_INTERVAL_mS (MICRO_DELAY_S * S_TO_mS_FACTOR)
#define MAX_IRRIGATION_TIME_mS (SHORT_HALF_DELAY_S * S_TO_mS_FACTOR)

struct Led
{
    uint8_t pin;
    bool on;

    void update()
    {
        digitalWrite(pin, on ? HIGH : LOW);
    }

    void toggle()
    {
        this->on = (!this->on);
        this->update();
    }
};

#endif // ifndef __AUTOWATER_MACRO_H__