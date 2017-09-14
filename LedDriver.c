#include "LedDriver.h"

void LedDriver_Create(volatile uint8_t* ledsAddress)
{
    *ledsAddress = 0;
}

void TurnLedOn(volatile uint8_t* ledsAddress, uint8_t ledNumber)
{
    /* 
     * Led numbering is 1-based indexed
     * but bitmasking by index is 0-based.
     * i.e. 2^0 == 1 == 0b0000_0001
     * and 2^4 == 16 == 0b0001_0000
     * So we must translate to a zero index before left shifting.
     */
    *ledsAddress |= (1 << (ledNumber - 1));
}
