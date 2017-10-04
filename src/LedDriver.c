#include <stdint.h>
#include "LedDriver.h"

void LedsOn(leds_t* leds)
{
    *leds = ON;
}

void LedsOff(leds_t* leds)
{
    *leds = OFF;
}

void LedOn(leds_t* leds, uint8_t ledNumber)
{
    /* 
     * Leds are 1 indexed, so we correct the index
     * then shift a one into that bit of an integer
     * finally, we apply the bitmask against the existing state
     */
    *leds |= (1 << (ledNumber - 1));
}

void LedOff(leds_t* leds, uint8_t ledNumber)
{
    *leds &= ~(1 << (ledNumber - 1));
}