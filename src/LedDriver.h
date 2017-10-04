#include <stdint.h>

typedef uint8_t leds_t;

void LedsOn(leds_t* leds);
void LedsOff(leds_t* leds);
void LedOn(leds_t* leds, uint8_t ledNumber);