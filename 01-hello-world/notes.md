
** Preprocessors actually predate most compilers, as it was a common way to extend an assembler, but now we're getting ahead (or behind) ourselves.

** For the record, `int` could technically be 64-bits on a 64-bit machine, but not usually.  Even on 64-bit versions of Linux, Mac OS X, and Windows, an `int` is still 32-bits.  Do a google search for `limits.h` or read your local copy of `/usr/include/limits.h` and follow the #include macros.  On my Mac, INT_MAX is defined in `/usr/include/i386/limits.h`.  `INT_MAX` and `INT_MIN` are preprocessor macros that you can use in your programs to inspect your system's actual size of `int`.  But if you're doing that in your program, you're probably doing it wrong.  If you really care about the exact size, most UNIX systems have `stdint.h` which has definitions for types like `int32_t`, `uint32_t`, `uint16_t`, etc. and that's what you should be using.  I use `int` most of the time, when I care mostly about speed, and I'm trying to express that it doesn't really matter what size the `int` actually is, as long as it can hold the value of my array index or counter or whatever.  If I'm on a tiny 16-bit microcontroller, I'm probably not using large arrays anyway, so those indexes will still fit.  In any case, I'll use `int` in all of my examples, until we need to go beyond that.


** The compiler turns your literal string in the source code into a sequence of bytes, and automatically puts the NUL at the end.  You can explicitly put a NUL into a string, using the '\0' character, but then that will fool `printf` into thinking it's the end of the string.  So if you change the code to `printf("Hello\0world!\n")` for example, then you'll just see "Hello".  `printf` stops there, and doesn't print the rest.  We'll dig into why later on.

** `printf` is declared in `/usr/include/stdio.h` (or one of the files it includes).  That's why we used "#include <stdio.h>" above.

** Whatever you return, you're only going to get the first 8 bits of the value.  On all computers these days, negative numbers are represented in twos-complement.  -1 is represented as all ones, or 0xFFFFFFFF in hex.  The bottom 8 bits are just 0xFF, which is postive 255.  So, returning -1 results in an exit status of 255.  Note that there's no "conversion" or anything going on to get from -1 to 255.  It's just looking at the last 8 bits of a 32-bit number.