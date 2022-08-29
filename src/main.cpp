#include <Arduino.h>
#include "macros.h"
#include "power.h"

RTC_DATA_ATTR bool pump_was_running = false;

void run_pump(int duration_in_ms=MAX_IRRIGATION_TIME_mS){
  //set the pin high
  digitalWrite(PUMP_CONTROL_PIN, LOW);
  //record time and flag
  Serial.println("Pump has started for " + String(duration_in_ms) + " milli seconds" );
  Serial.flush();
  int duration_in_sec = duration_in_ms / S_TO_mS_FACTOR;
  for(int i = 0; i < duration_in_sec; i++)
  {
    delay(1000);
  }
  //set the pin low
  digitalWrite(PUMP_CONTROL_PIN, HIGH);
  //pump is stopped
  Serial.println("Pump is stopped");
}

int get_dryness_level(int num_retries=3){
  int dryness_level = 0;
  for(int i=0; i < num_retries; i++){
    dryness_level = analogRead(SOIL_INPUT_PIN1);
    delay(100);
    Serial.println("dryness_level#" + String(i) + ": " + String(dryness_level) );
  }
  return dryness_level;
}

void setup() {

  Serial.begin(9600);
  //wait for sometime to serial wakeup
  delay(1000);

  //print wakeup reason
  print_wakeup_reason();
  
  // put your setup code here, to run once:
  //pinMode(SOIL_INPUT_PIN1, INPUT);
  //pinMode(SOIL_INPUT_PIN2, INPUT);
  pinMode(PUMP_CONTROL_PIN, OUTPUT);
  //keep the pump is stopped condition
  digitalWrite(PUMP_CONTROL_PIN, HIGH);
  delay(5000);

  //check soil moisture level
  int dryness_level = get_dryness_level();
  Serial.println("current dryness level: " + String(dryness_level) );
  //check required dryness settings
  int dryness_settings = analogRead(POTENTIOMETER_PIN);
  //int required_dryness_level = DRYNESS_THRESHOLD_HIGH - ( (DRYNESS_THRESHOLD_HIGH - DRYNESS_THRESHOLD_LOW) * (dryness_settings / DRYNESS_LEVELS) ) ;
  int required_dryness_level = map(dryness_settings, 0, 4095, DRYNESS_THRESHOLD_HIGH, DRYNESS_THRESHOLD_LOW ) ;
  Serial.println("required dryness level: " + String(required_dryness_level) );
  if( (dryness_level > (required_dryness_level + DRYNESS_OFFSET) ) ||
        ((dryness_level > required_dryness_level) && (pump_was_running)) ){
    //PUMP needs to be started if it is too dry or 
    //during last cycle pump was running and required level was not achieved

    //run the pump for some time
    Serial.println("Soil is dry. Pump is starting");
    run_pump();
    pump_was_running=true;
    //give a rest to pump and the system
    deep_sleep(PUMP_REST_TIME_mS);
    //delay(PUMP_REST_TIME_mS);
  }
  else{
    Serial.println("Soil is OK. long rest");
    pump_was_running = false;
    deep_sleep(DEEP_SLEEP_TIME_mS);
    //delay(DEEP_SLEEP_TIME_mS);
  }
}


void loop() {
  //in deep sleep mode loop method is empty
}

