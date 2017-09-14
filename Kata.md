# LED Driver Kata

You've been asked to develop an LED Driver for ACME Co.'s new device.
The hardware isn't ready yet, but the specs are looking pretty good.

The device will have 8 memory mapped, single color, LEDs.
The pins are active HIGH.
On power up, the hardware turns the lights on.

The low bit maps to LED1; high bit to LED8.

| Bit | LED |
| --- | --- |
|  0  |  1  |
|  1  |  2  |
|  2  |  3  |

etc.


## Stories
- [x] On initialization, turn all the LEDs off
- [ ] Turn all the LEDs On
- [x] Turn a Single LED On
- [ ] Turn a Single LED Off
