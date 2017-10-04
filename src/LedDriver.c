#include <stdint.h>
#include "LedDriver.h"

void LedsOn(leds_t* leds)
{
    *leds = 0xff;
}

void LedsOff(leds_t* leds)
{
    *leds = 0x00;
}