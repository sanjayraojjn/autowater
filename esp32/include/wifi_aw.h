#ifndef __AUTOWATER_WIFI_H__
#define __AUTOWATER_WIFI_H__

#include <WiFiManager.h>
#include <WiFi.h>

#include <macros.h>

void setupWiFi()
{
  WiFi.mode(WIFI_STA);

  // wifi manager local initialization
  WiFiManager wm;
  // for testing
  // wm.resetSettings();

  // wifimanager will try to connect
  bool res = wm.autoConnect("autowater", "autowater");

  if (!res)
  {
    __PL("unable to connect wifi");
  }
  else
  {
    __PL("wifi connection is setup");
  }
}

/*
//wifi parameters
const char* WIFI_SSID = "C503_airtel";
const char* WIFI_PASS = "c503airtel";

void initWiFi(){
  WiFi.mode(WIFI_STA);
  WiFi.begin(WIFI_SSID, WIFI_PASS);
  Serial.printf("Trying to connect wifi...[%s]", WiFi.macAddress().c_str() );
  while(WiFi.status() != WL_CONNECTED){
    Serial.printf(".");
    delay(500);
  }
  Serial.printf("wifi connected %s EFP32-%0X", WiFi.localIP().toString().c_str(), ESP.getEfuseMac() );
}
*/

#endif //__AUTOWATER_WIFI_H__