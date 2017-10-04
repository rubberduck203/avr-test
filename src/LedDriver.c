#include <stdint.h>
#include "LedDriver.h"

void LedsOn(uint8_t* leds)
{
    *leds = 0xff;
}