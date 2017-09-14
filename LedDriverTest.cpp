#include "CppUTest/TestHarness.h"

extern "C"
{
    #include "LedDriver.h"
}

TEST_GROUP(LedDriver)
{
};

TEST(LedDriver, LedsAreOffAfterCreate)
{
  uint8_t virtualLeds = 0xff;
  LedDriver_Create(&virtualLeds);
  LONGS_EQUAL(0, virtualLeds);
}

TEST(LedDriver, TurnOnLED1)
{
  uint8_t virtualLeds = 0xff;
  LedDriver_Create(&virtualLeds);
  
  TurnLedOn(&virtualLeds, 1);

  BYTES_EQUAL(0x01, virtualLeds);
}

TEST(LedDriver, TurnOnLed2)
{
  uint8_t virtualLeds = 0xff;
  LedDriver_Create(&virtualLeds);

  TurnLedOn(&virtualLeds, 2);

  BYTES_EQUAL(0x02, virtualLeds);
}


