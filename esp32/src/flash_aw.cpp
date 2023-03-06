#include <Preferences.h>

#include <macros.h>
#include <flash_aw.h>

uint8_t getUChar(char *name)
{
    Preferences perferences;
    // open it in read only mode.
    perferences.begin(APPNAME);

    // read from perferences
    uint8_t req_moist = perferences.getUChar(name, (uint8_t)DEFAULT_REQUIRED_MOIST);

    // close perferences
    perferences.end();

    return req_moist;
}
