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

void LedOn(leds_t* leds, uint8_t ledNumber)
{
    /* 
     * Leds are 1 indexed, so we correct the index
     * then shift a one into that bit of an integer
     * finally, we apply the bitmask
     */
    *leds = ON & (1 << (ledNumber - 1));
}