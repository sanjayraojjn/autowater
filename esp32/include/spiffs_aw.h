#ifndef __AUTOWATER_SPIFFS_H__
#define __AUTOWATER_SPIFFS_H__

#include <SPIFFS.h>
#include <macros.h>
#include <base.h>

extern Led onboard_led;

void initSPIFFS()
{
  if (!SPIFFS.begin())
  {
    __PL("cannot mount SPIFFS volume...");
    while (1)
    {
      onboard_led.on = millis() % 200 < 50;
      onboard_led.update();
    }
  }
}

#endif //__AUTOWATER_SPIFFS_H__