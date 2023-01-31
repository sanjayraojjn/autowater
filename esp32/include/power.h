#include <Arduino.h>
#include "macros.h"

#ifndef __POWER_H__
#define __POWER_H__


void print_wakeup_reason(esp_sleep_wakeup_cause_t cause){

  switch(cause){
    case ESP_SLEEP_WAKEUP_EXT0:
      Serial.println("wakeup by external signal using RTC_IO");
      break;
    case ESP_SLEEP_WAKEUP_EXT1:
      Serial.println("wakeup by external signal RTC_CNTL");
      break;
    case ESP_SLEEP_WAKEUP_TIMER:
      Serial.println("wakeup by timer");
      break;
    case ESP_SLEEP_WAKEUP_TOUCHPAD:
      Serial.println("wakeup by touchpad");
      break;
    case ESP_SLEEP_WAKEUP_ULP:
      Serial.println("wakeup by ULP program");
      break;
    default:
      Serial.println("wakeup by not caused by deep sleep");
      break;    
  }  
}

void deep_sleep(int duration_in_msec=PUMP_REST_TIME_mS){
    //setup ESP32 to sleep in timer mode
    esp_sleep_enable_timer_wakeup(duration_in_msec * mS_TO_uS_FACTOR);

    Serial.println("processor is going to sleep now for " + String(duration_in_msec) + " msec");
    delay(1000);
    Serial.flush();
    esp_deep_sleep_start();
    Serial.println("this will never be printed");
}


void print_wakeup_reason(){
  //find out the reason of wakeup
  esp_sleep_wakeup_cause_t cause;
  cause = esp_sleep_get_wakeup_cause();

  switch(cause){
    case ESP_SLEEP_WAKEUP_EXT0:
      Serial.println("wakeup by external signal using RTC_IO");
      break;
    case ESP_SLEEP_WAKEUP_EXT1:
      Serial.println("wakeup by external signal RTC_CNTL");
      break;
    case ESP_SLEEP_WAKEUP_TIMER:
      Serial.println("wakeup by timer");
      break;
    case ESP_SLEEP_WAKEUP_TOUCHPAD:
      Serial.println("wakeup by touchpad");
      break;
    case ESP_SLEEP_WAKEUP_ULP:
      Serial.println("wakeup by ULP program");
      break;
    default:
      Serial.println("wakeup is not caused by deep sleep");
      break;    
  }  
}



#endif   //__POWER_H__
