#include <stdint.h>

void TurnLedsOn(volatile uint8_t* ledsAddress);
void TurnLedsOff(volatile uint8_t* ledsAddress);

void TurnLedOn(volatile uint8_t* ledsAddress, uint8_t ledNumber);