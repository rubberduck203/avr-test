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
