
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

Open Source Version of Atmel's Flip Tool for \*nix based systems.
Needed for interfacing with Eval board's USB bootloader.

http://dfu-programmer.github.io/
