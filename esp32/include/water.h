#ifndef __AUTOWATER_WATER_H__
#define __AUTOWATER_WATER_H__

class AutoWaterCheck
{
private:
public:
    void operator()();
};

void check_water()
{
    AutoWaterCheck check;
    check();
}

class AutoWater
{
private:
public:
    void operator()();
};

void water_plant()
{
    AutoWater water;
    water();
}

#endif //__AUTOWATER_WATER_H__