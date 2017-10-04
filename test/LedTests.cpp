#include <stdint.h>
#include "CppUTest/TestHarness.h"

extern "C"
{
    #include "../src/LedDriver.h"
}

TEST_GROUP(FirstTestGroup)
{
};

TEST(FirstTestGroup, TurnAllLedsOn)
{
    uint8_t leds = 0x00;
    LedsOn(&leds);
    BYTES_EQUAL(0xff, leds);
}

TEST(FirstTestGroup, TurnAllLedsOff)
{
    uint8_t leds = 0xff;
    LedsOff(&leds);
    BYTES_EQUAL(0x00, leds);
}