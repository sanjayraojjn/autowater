#include <Arduino.h>

#define PUMP_CONTROL_PIN 14
#define SOIL_INPUT_PIN1 33
#define SOIL_INPUT_PIN2 32
#define POTENTIOMETER_PIN 35

//#define DEV_FLAG 1

#define DRYNESS_THRESHOLD_HIGH 2800
#define DRYNESS_THRESHOLD_LOW 1200
#define DRYNESS_LEVELS 4096
#define DRYNESS_OFFSET 200

//time intervals

//in development environment
#ifdef DEV_FLAG

//30 seconds or 5 minutes
#define LONG_DELAY 30000 
//6 seconds
#define SHORT_DELAY 6000  
//3 seonds
#define SHORT_HALF_DELAY 3000
//1 second
#define MICRO_DELAY 1000

#else

//300 seconds or 5 minutes
#define LONG_DELAY 300000 
//60 seconds or 1 minutes
#define SHORT_DELAY 60000 
//30 seonds
#define SHORT_HALF_DELAY 30000 
//10 seconds
#define MICRO_DELAY 10000

#endif


//300 seconds or 5 minutes
#define PUMP_REST_TIME LONG_DELAY    
//300 seconds or 5 minutes
#define SENSOR_CHECK_INTERVAL LONG_DELAY    
//every 10 seconds
#define PUMP_RUNNING_CHECK_INTERVAL MICRO_DELAY   
//60 seconds
#define MAX_IRRIGATION_TIME SHORT_HALF_DELAY 

void setup() {
  Serial.begin(9600);
  
  // put your setup code here, to run once:
  //pinMode(SOIL_INPUT_PIN1, INPUT);
  //pinMode(SOIL_INPUT_PIN2, INPUT);
  pinMode(PUMP_CONTROL_PIN, OUTPUT);
  //set the pin low
  digitalWrite(PUMP_CONTROL_PIN, LOW);
}

bool is_pump_running = false;
unsigned long pump_started_at = 0;
unsigned long pump_stopped_at = 0;
unsigned long last_checked_at = 0;
int last_required_dryness_level = 0;
bool first_run = true;

void start_pump(){
  //set the pin high
  digitalWrite(PUMP_CONTROL_PIN, HIGH);
  //record time and flag
  is_pump_running = true;
  pump_started_at = millis();
  Serial.println("Pump has started");
}

void stop_pump(){
  //set the pin low
  digitalWrite(PUMP_CONTROL_PIN, LOW);
  //record time and flag
  is_pump_running = false;
  pump_stopped_at = millis();
  Serial.println("Pump has stopped");
}

void rest_pump(){
  stop_pump();
  delay(PUMP_REST_TIME);
}

int get_dryness_level(int num_retries=5){
  int dryness_level = 0;
  for(int i=0; i < num_retries; i++){
    dryness_level = analogRead(SOIL_INPUT_PIN1);
    delay(100);
    Serial.print("dryness_level#");
    Serial.print(i);
    Serial.print(": ");
    Serial.println(dryness_level);
  }
  return dryness_level;
}

void loop() {

  unsigned long current_time = millis();

  if(is_pump_running){

    if( (current_time - last_checked_at) > PUMP_RUNNING_CHECK_INTERVAL ){
      //read sensor dryness level
      int dryness_level = get_dryness_level();
      Serial.print("current dryness level ");
      Serial.println(dryness_level);
      Serial.print("required level is ");
      Serial.println(last_required_dryness_level);
      if( dryness_level < (last_required_dryness_level - DRYNESS_OFFSET) ){
        //required irrigation has been done
        Serial.println("dryness level has reached to required level, stopping pump");
        stop_pump();
        delay(LONG_DELAY);
      }
      else if( (current_time - pump_started_at) >  MAX_IRRIGATION_TIME ){
        //motor needs a rest
        Serial.println("Maximum irrigation time reached. Pump is going to rest");
        rest_pump();
      }
      last_checked_at = millis();
      delay(MICRO_DELAY);
    }
  }
  else{
    bool pump_has_rested = (current_time - pump_stopped_at) > PUMP_REST_TIME;
    bool test_threshold_reached = (current_time - last_checked_at) > SENSOR_CHECK_INTERVAL;

    if ( first_run || (pump_has_rested && test_threshold_reached) ){
      int dryness_level = get_dryness_level();
      int dryness_settings = analogRead(POTENTIOMETER_PIN);
      Serial.print("current dryness level ");
      Serial.println(dryness_level);
      
      //record last sensor data time
      last_checked_at = millis();

      //int required_dryness_level = DRYNESS_THRESHOLD_HIGH - ( (DRYNESS_THRESHOLD_HIGH - DRYNESS_THRESHOLD_LOW) * (dryness_settings / DRYNESS_LEVELS) ) ;
      int required_dryness_level = map(dryness_settings, 0, 4095, DRYNESS_THRESHOLD_HIGH, DRYNESS_THRESHOLD_LOW ) ;
      Serial.print("required level is ");
      Serial.println(required_dryness_level);
      Serial.print("dryness settings is ");
      Serial.println(dryness_settings);
      if(dryness_level > (required_dryness_level + DRYNESS_OFFSET)){   //PUMP needs to be started
        //start the pump
        Serial.println("Soil is dry. Pump is starting");
        start_pump();
        //record the last required_dryness_level
        //it is important to record becasue required_level can be changed while irrigation is going on
        last_required_dryness_level = required_dryness_level;
      }
      else{
        Serial.println("Soil is OK. rest");
        delay(LONG_DELAY);
      }
    }
    else{
      Serial.println("It is too early to check again.");
      delay(LONG_DELAY);
    }
  }


  //Serial.print("moist level#1 is ");
  //Serial.println(moist_level1);
  //Serial.print("moist level#2 is ");
  //Serial.println(moist_level2);
  //Serial.print("moist_setting=");
  //Serial.println(dryness_settings);



  //if(moist_level > 2000){
  //  digitalWrite(PUMP_CONTROL_PIN, HIGH);
  //}
  //else{
  //  digitalWrite(PUMP_CONTROL_PIN, LOW);
  //}

  //delay(500);
}