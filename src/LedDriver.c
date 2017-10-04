#include <stdint.h>
#include "LedDriver.h"

void LedsOn(volatile leds_t* leds)
{
    *leds = ON;
}

void LedsOff(volatile leds_t* leds)
{
    *leds = OFF;
}

leds_t indexToBitmask(uint8_t ledNumber)
{
    /* 
     * Leds are 1 indexed, so we correct the index
     * then shift a one into that bit of an integer
     */
    return 1 << (ledNumber - 1);
}

void LedOn(volatile leds_t* leds, uint8_t ledNumber)
{
    *leds |= indexToBitmask(ledNumber);
}

void LedOff(volatile leds_t* leds, uint8_t ledNumber)
{
    *leds &= ~indexToBitmask(ledNumber);
}