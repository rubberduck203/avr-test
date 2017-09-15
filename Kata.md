# LED Driver Kata

You've been asked to develop an LED Driver for ACME Co.'s new device.
The hardware isn't ready yet, but the specs are looking pretty good.

The device will have 8 memory mapped, single color, LEDs.
The pins are active HIGH.
On power up, the hardware turns the lights on.

The low bit maps to LED1; high bit to LED8.

|     |   |   |   |   |   |   |   |   |
| --- | - | - | - | - | - | - | - | - |
| Bit | 7 | 6 | 5 | 4 | 3 | 2 | 1 | 0 |
| LED | 8 | 7 | 6 | 5 | 4 | 3 | 2 | 1 |

## Stories
- [x] On initialization, turn all the LEDs off
- [x] Turn all the LEDs On
- [x] Turn a Single LED On
- [x] Turn a Single LED Off
- [x] Oh crap! The pins are active LOW not HIGH!
- [ ] Start up sequence

Notes:

- The first several stories are straight forward.
- The "Oh crap" story was inspired by the actual board I downloaded this code to.
I didn't initially intend to actually run this on a target, but when I did I discovered that all the lights were turning *off* in sequence instead of on.
It seems like it would be a common enough problem, and worth thinking about how to make it as easy as possible to change both the tests and production code if this happens.
- Start up sequence is intended to create drive a need to create a higher level domain context that uses the LedDriver.

