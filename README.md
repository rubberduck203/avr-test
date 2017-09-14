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

### TODO

 1. Put code from `src` directory under test.
 2. Make sure we can copmile that code with the avr compiler.

---

[Interesting article about using CppUTest](https://www.sparkpost.com/blog/getting-started-cpputest/)

---

Open Source Version of Atmel's Flip Tool for \*nix based systems.
Needed for interfacing with Eval board's USB bootloader.

http://dfu-programmer.github.io/
