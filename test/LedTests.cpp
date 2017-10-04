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
    leds_t leds = OFF;
    LedsOn(&leds);
    BYTES_EQUAL(ON, leds);
}

TEST(LedDriverTests, TurnAllLedsOff)
{
    leds_t leds = ON;
    LedsOff(&leds);
    BYTES_EQUAL(OFF, leds);
}

TEST(LedDriverTests, TurnLedOneOn)
{
    leds_t leds = OFF;
    LedOn(&leds, 1);
    BYTES_EQUAL(0x01, leds);
}

TEST(LedDriverTests, TurnLedTwoOn)
{
    leds_t leds = OFF;
    LedOn(&leds, 2);
    BYTES_EQUAL(0x02, leds);
}

TEST(LedDriverTests, TurnLedSevenOn)
{
    leds_t leds = OFF;
    LedOn(&leds, 7);
    BYTES_EQUAL(0x40, leds);
}

TEST(LedDriverTests, TurnMultipleLedsOn)
{
    leds_t leds = OFF;
    LedOn(&leds, 1);
    LedOn(&leds, 7);
    BYTES_EQUAL(0x41, leds);
}

TEST(LedDriverTests, TurnLedThreeOff)
{
    leds_t leds = ON;
    LedOff(&leds, 3);
    BYTES_EQUAL(0xfb, leds);
}