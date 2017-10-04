#include <stdint.h>
#include "CppUTest/TestHarness.h"

extern "C"
{
    #include "../src/LedDriver.h"
}

TEST_GROUP(LedDriverTests)
{
};

TEST(LedDriverTests, TurnAllLedsOn)
{
    leds_t leds = 0x00;
    LedsOn(&leds);
    BYTES_EQUAL(0xff, leds);
}

TEST(LedDriverTests, TurnAllLedsOff)
{
    leds_t leds = 0xff;
    LedsOff(&leds);
    BYTES_EQUAL(0x00, leds);
}

TEST(LedDriverTests, TurnLedOneOn)
{
    leds_t leds = 0x00;
    LedOn(&leds, 1);
    BYTES_EQUAL(0x01, leds);
}