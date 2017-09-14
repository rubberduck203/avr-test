#include <stdint.h>

void TurnLedsOff(volatile uint8_t* ledsAddress);
void TurnLedOn(volatile uint8_t* ledsAddress, uint8_t ledNumber);
void TurnAllLedsOn(volatile uint8_t* ledsAddress);