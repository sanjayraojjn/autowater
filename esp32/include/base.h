#ifndef __AUTOWATER_BASE_H__
#define __AUTOWATER_BASE_H__

#include <Arduino.h>

#include <macros.h>

#ifdef DEV_FLAG

#define __PL(a) Serial.println(a)
#define __PP(a) Serial.print(a)

#else // DEV_FLAG

#define __PL(a)
#define __PP(a)

#endif // DEV_FLAG

#endif //__AUTOWATER_BASE_H__