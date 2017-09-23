# LED Driver Kata

You've been asked to develop an LED Driver for ACME Co.'s new device.
The hardware isn't ready yet, but the specs are looking pretty good.

The device will have 8 memory mapped, single color, LEDs.
The pins are active HIGH.
On power up, all of the lights are off.

The low bit maps to LED1; high bit to LED8.

|     |   |   |   |   |   |   |   |   |
| --- | - | - | - | - | - | - | - | - |
| Bit | 7 | 6 | 5 | 4 | 3 | 2 | 1 | 0 |
| LED | 8 | 7 | 6 | 5 | 4 | 3 | 2 | 1 |

Since the target hardware isn't available yet, the tests must be runnable from the host OS.
We do know that we'll be using the [Atmel ATxmega128a1][atxmega128a1] mcu though, so the solution must also compile with the [avr-gcc compiler][avr-gcc].

## Development Environment

- Host Compiler: [gcc][gcc]
- Target Compiler: [avr-gcc][avr-gcc]
- Test Framework: [CppUTest][cpputest]
- Build: [make][make]

For convenience, a docker image is provided with these dependencies pre-installed.
The following command will start the build tools container and mount the current working directory.

```bash
# from the project root directory
docker run --rm -it -v ${PWD}:/mount rubberduck/avr
```

[atxmega128a1]: http://www.microchip.com/wwwproducts/en/ATxmega128A1
[avr-gcc]: http://www.nongnu.org/avr-libc/user-manual/install_tools.html
[gcc]: https://gcc.gnu.org/
[cpputest]: https://cpputest.github.io/
[make]: https://www.gnu.org/software/make/

## Stories
- [x] Turn all the LEDs Off
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

