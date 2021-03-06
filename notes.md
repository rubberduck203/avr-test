# Dual Targeting gcc/avr-gcc

## Summary

Experiment to see if I can set up a dev environment to build and test against both the gcc and the avr-gcc compiler. 
The goal is to be able to run unit tests locally, and then compile with avr-gcc to upload to the target device.

## Notes
I already had gcc installed via xcode.

> gcc --version
> Configured with: --prefix=/Applications/Xcode.app/Contents/Developer/usr --with-gxx-include-dir=/usr/include/c++/4.2.1
> Apple LLVM version 8.1.0 (clang-802.0.42)
> Target: x86_64-apple-darwin16.7.0
> Thread model: posix
> /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin

Next [install avr-gcc via homebrew](https://github.com/osx-cross/homebrew-avr).

```bash
brew tap osx-cross/avr
brew install avr-gcc
```

Grab a coffee...
This took about an hour.

> 🍺  /usr/local/Cellar/avr-gcc/7.2.0: 1,682 files, 174.9MB, built in 56 minutes 45 seconds    

---

Meanwhile...

Verify we can compile with gcc.

http://www.network-theory.co.uk/docs/gccintro/gccintro_9.html

```c
#include <stdio.h>

int
main (void)
{
  printf ("Hello, world!\n");
  return 0;
}
```

```bash
gcc -Wall hello.c -o hello
```

---

## Tests

I chose CppUTest at the recommendation of James Greening via his book TDD for Embedded C.
Setup [CppUTest](https://cpputest.github.io/)

```bash 
brew install cpputest
```

https://stackoverflow.com/questions/18453742/cpputest-example-doesnt-work

> Undefined symbols for architecture x86_64:   
> ...

After a bit of fussing around, created this command that compiles.

```bash
g++ -I/usr/local/Cellar/cpputest/3.8/include \
   -L/usr/local/Cellar/cpputest/3.8/lib -lCppUTest -lCppUTestExt \
   helloTest.cpp AllTests.cpp 
``` 

And then run the tests with `./a.out`

The trouble was I wasn't properly linking in the CppUTest libary when trying to compile.
Created a makefile in the `test` directory to make compiling repeatable.

```bash
cd test
make
bin/test -c #-c colorizes output
```

Improve make by changing `make test` to build and run tests.


```make
#CppUTest
CPPUTEST_HOME = /usr/local/Cellar/cpputest/3.8
CPPFLAGS += -I$(CPPUTEST_HOME)/include
CXXFLAGS += -include $(CPPUTEST_HOME)/include/CppUTest/MemoryLeakDetectorNewMacros.h
CFLAGS += -include $(CPPUTEST_HOME)/include/CppUTest/MemoryLeakDetectorMallocMacros.h
LD_LIBRARIES = -L$(CPPUTEST_HOME)/lib -lCppUTest -lCppUTestExt
```

---

[Interesting article about using CppUTest](https://www.sparkpost.com/blog/getting-started-cpputest/)

---

## Compiling for avr target

- Add an `avr` target to make file.

```bash
avr-gcc -Wall -mmcu=atxmega128a1 -Os -g -c LedDriver.c -o bin/LedDriver.o
```

- Add a main program for the avr. This file should do *very* little. Just delegate off.

```c
#include "LedDriver.h"

int main(void)
{
    // Just here to make sure we can link
    // Implementation will come later
    return 0;
}
```

```bash
avr-gcc -Wall -mmcu=atxmega128a1 -g -c Main.c -o bin/Main.o
```

- Add link to `avr` make target.

```bash
avr-gcc -Wall -mmcu=atxmega128a1 -g bin/LedDriver.o bin/Main.o -o bin/demo.elf
```

- Extract hex file from elf to upload
- update Main.c to toggle all lights on and off to verify dfu-programmer works


## Upload to target device

Open Source Version of Atmel's Flip/BatchISP Tool for \*nix based systems.
Needed for interfacing with Eval board's USB bootloader.

http://dfu-programmer.github.io/

I'm running on a \*nix machine, so I can't use FLIP to upload to the bootloader on my xplained.

```bash
git clone https://github.com/dfu-programmer/dfu-programmer.git
cd dfu-programmer
```

follow instructions in readme

**Holy crap what a PITA.**

So, dfu-programmer doesn't work with Mac because libusb doesn't seem to play well and something in the MacOs is lockging the serial port so dfu-programmer can't get a handle on it.
That's *after* [I modified the table in order to add support for x128a1][1] (it already supports x128a1u).

[1]:https://github.com/rubberduck203/dfu-programmer/commit/396e093edfdba7f5a1c8c2bf529556a63269e774

So, I ditched that and tried Avrdude because flip support was added recently.
No dice. I'm getting a very similar error.

- pid = 0x2122

I've had to resort to programming it on a windows machine I have around here using FLIP.

Oh, and don't forget to copy this xml file into `Flip 3.4.2\bin\PartDescriptionFiles` or it won't work either.

- [ATxmega Xplained - Getting Started Guide](http://www.atmel.com/Images/doc8372.pdf) 
- [Atxmega Xplained - Getting Started Guide App Notes Download](http://www.atmel.com/images/AVR1924.zip)

#### ATxmega128a1.xml

```xml
<?xml version="1.0"?>
<!DOCTYPE Part SYSTEM "part.dtd">
<Part NAME="ATxmega128A1">
	<PageSize SIZE="512" />

	<Memory NAME="FLASH"         SIZE="131072" ADDR="0"  INDEX="0"/>
	<Memory NAME="EEPROM"        SIZE="2048"   ADDR="0"  INDEX="1"/>
	<Memory NAME="BOOTLOADER"    SIZE="3"                INDEX="3"/>
	<Memory NAME="SIGNATURE"     SIZE="4"                INDEX="6"/>
	<Memory NAME="USER"          SIZE="512"              INDEX="11"/>
	
	<Protocol FILE="RS232_I03.xml" />
</Part>
```

I eventually gave up and just used Windows and Batchisp/Flip to flash the device.

## Docker

I put together a docker image to document the necessary tools and make the build environment repeatable.

### Build Image

```bash
docker build -t rubberduck/avr .
```

### Run Image As Build Tool

This command will run the container and mount the current working directory to the working directory of the container. 
Mounting the current container means we leave the build artifacts behind on the host machine.

```bash
docker run --rm -it -v ${PWD}:/mount rubberduck/avr
```

This means I needed to modify the make file to use environment variables to obtain cpputest file locations, because brew puts them all into one place, but on ubuntu, the files are scattered around.

If using Mac, add the following variables to your ~/.bash_profile.

```bash
export CPPUTEST_HOME=/usr/local/Cellar/cpputest/3.8
export CPPUTEST_INCLUDE=$CPPUTEST_HOME/include
export CPPUTEST_LIB=$CPPUTEST_LIB/lib
```

Change Makefile variables to look like this.

```make
CPPFLAGS += -I$(CPPUTEST_INCLUDE)
CXXFLAGS += -include $(CPPUTEST_INCLUDE)/CppUTest/MemoryLeakDetectorNewMacros.h
CFLAGS += -include $(CPPUTEST_INCLUDE)/CppUTest/MemoryLeakDetectorMallocMacros.h
LD_LIBRARIES = -L$(CPPUTEST_LIB) -lCppUTest -lCppUTestExt
```

First fun error happens

> undefined reference to 'UtestShell::getCurrent()'

[Need to re-order the link command so that library comes last.](https://groups.google.com/forum/#!topic/cpputest/GnlxTVf8i8w)

Next fun error happens

> Main.c:19:9: error: 'for' loop initial declarations are only allowed in C99 or C11 mode

Add `-std=c11` arg to avr target to use newest syntax.


*Don't set those environment variables at all. Use pkg-config instead.*

```make
CPPFLAGS += $(shell pkg-config --cflags cpputest)
CXXFLAGS += -include CppUTest/MemoryLeakDetectorNewMacros.h
CFLAGS += -include CppUTest/MemoryLeakDetectorMallocMacros.h
LD_LIBRARIES = $(shell pkg-config --libs cpputest)
```
