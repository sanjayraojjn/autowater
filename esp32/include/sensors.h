#ifndef __AUTOWATER_SENSORS_H__
#define __AUTOWATER_SENSORS_H__

int get_dryness_level(int pin_num = SOIL_INPUT_PIN1, int num_retries = 3);

long get_required_moist_level();

#endif //__AUTOWATER_SENSORS_H__