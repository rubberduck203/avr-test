//#include <stdint.h>
#include "CppUTest/TestHarness.h"
#include "mocks/include/avr/io.h"

extern "C"
{
    #include "../src/Run.h"
}

TEST_GROUP(RunTests)
{
};

TEST(RunTests, SetupForOutput)
{
    Setup();
    BYTES_EQUAL(0xff, PORTE.DIR);
}

TEST(RunTests, LedsRegisterAssignedToPORTE)
{
    Setup();
    POINTERS_EQUAL(&PORTE.OUT, leds);
}
