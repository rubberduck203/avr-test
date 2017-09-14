#include "LedDriver.h"

void TurnLedsOff(volatile uint8_t* ledsAddress)
{
    *ledsAddress = 0x00;
}

void TurnAllLedsOn(volatile uint8_t* ledsAddress)
{
    *ledsAddress = 0xff;
}

uint8_t LedNumberToBitMask(uint8_t ledNumber)
{
    /* 
     * Led numbering is 1-based indexed
     * but bitmasking by index is 0-based.
     * i.e. 2^0 ==  1 == 0b0000_0001
     * and  2^4 == 16 == 0b0001_0000
     * So we must translate to a zero index before left shifting.
     */
    return 1 << (ledNumber - 1);
}

void TurnLedOn(volatile uint8_t* ledsAddress, uint8_t ledNumber)
{
    *ledsAddress |= LedNumberToBitMask(ledNumber);
}