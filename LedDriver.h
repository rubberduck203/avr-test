#include <stdint.h>

void LedDriver_Create(volatile uint8_t* ledsAddress);
void TurnLedOn(volatile uint8_t* ledsAddress, uint8_t ledNumber);
void TurnAllLedsOn(volatile uint8_t* ledsAddress);