#include "CppUTest/TestHarness.h"

extern "C"
{
    #include "LedDriver.h"
}

TEST_GROUP(FirstTestGroup)
{
};

TEST(FirstTestGroup, FirstTest)
{
   CHECK_EQUAL(2,2);
}

TEST(FirstTestGroup, LedsAreOffAfterCreate)
{
  uint8_t virtualLeds = 0xff;
  LedDriver_Create(&virtualLeds);
  LONGS_EQUAL(0, virtualLeds);
}
