#include "LedDriver.h"

void LedDriver_Create(uint8_t* ledsAddress)
{
    *ledsAddress = 0;
}

void TurnLedOn(uint8_t* ledsAddress, uint8_t ledNumber)
{
    *ledsAddress |= ledNumber;
}
