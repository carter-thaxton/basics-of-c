separate-compilation
====================

Separate compilation is an important concept in C.  It lets you compile less than all of your code when you make incremental changes to source files.  It's also used for precompiling libraries, and then not having to recompile them just because you changed your program.  In fact, your system comes with many precompiled libraries that will likely never be recompiled even if they could be.  Yet, you use them every day, both when developing software, and when just using your computer.

This is related to a deep idea in computer science:  separate the things that change from the things that don't.

Look, we all know everything changes.  There's one constant in the universe, and all that...  But not everything changes at the same rate.  So, maybe that should be worded as:  group things that change at similar rates, and separate things that change at different rates.  But alas, it's not as catchy.

So, if we're going to have parts of our programs compiling at different rates, how do the parts connect up?  There must be a boundary or "interface" around each stable component.  As long as the interface does not change, then any changes to the "implementation" of a component can be recompiled without changing any other components.  This is true not just for the parts of your program, but for the program as a whole, including any external dependencies, like `printf`.  If any of the interfaces change, then more parts of the system are impacted, and more of the program (possibly all of it) must be recompiled.  Usually, however, such interface changes are still very minimal, in that when interfaces within your program change, you still don't need to recompile any of your external dependencies.  You don't need to recompile the stdio library and build a new version of `printf` just because you made a big refactor to your program.

Let's suppose we have a library called `simple_math`, which does some basic operations like `add`, `multiply`, and so on.  Nevermind that there are built-in C operators for these.  It's an example.

#### simple_math.h
```
#ifndef SIMPLE_MATH_H
#define SIMPLE_MATH_H

int add(int x, int y);
int multiply(int x, int y);

#endif
```

#### simple_math.c
```
#include "simple_math.h"

int add(int x, int y) {
  return x + y;
}

int multiply(int x, int y) {
  return x * y;
}
```

In C, we separate our "header files" from our "source files".  A header file *declares* an *interface* to a component, and a source file *defines* an *implementation*.  Other components of the system depend only on the interface of the component, and they never see the implementation.

To use a component, you `#include` a header file.  The contents of header files should only be *declarations*, not *definitions*.

There's an important rule in C: Declarations must precede their use.

Declarations tell the compiler about the *type* of something.  As the compiler parses code, it builds up a dictionary in RAM of declarations by name.  This dictionary contains types.  So, in our case of parsing `simple_math.h`, the compiler would create two entries: one for `add` and one for `multiply`.  For each entry, it stores the type, e.g. the fact that it is a function, and the *signature* of the function.  A signature is just a fancy name for how many parameters (the arity) and types of those parameters, as well as the type of the return value.  It uses this information when it encounters the use of an identifier, like a call to a function, e.g. `printf`.  As it parses the call, it checks that the types match what arguments are being passed, and does various book-keeping.

Now you can understand why we `#include <stdio.h>` in our original example.  If the compiler didn't see the declarations in that header file, it would have no ideas what `printf` is when we use it down below.

Let's ignore the preprocessor macros that say `#ifndef`, `#define`, and `#endif`.  I'll come back and explain that soon enough.

Unlike our 'hello' example, this component doesn't have a `main` function.  Nor should it.  It's not intended to be the entry point of a program.  It's intended to be used from other parts of a larger program.

Let's see how we would use it.

#### main.c
```
#include <stdio.h>
#include "simple_math.h"

int main(int argc, char *argv[]) {
  int sum = add(5, 2);
  int product = multiply(3, 7);

  printf("5 + 2: %d\n", sum);
  printf("3 * 7: %d\n", product);

  return 0;
}
```

This time we have a source file that defines a `main` function, but before it calls `add` or `multiply`, it uses the preprocessor to `#include "simple_math.h` to put the declarations of those functions before their use.  Remember, the preprocessor just literally inlines the contents of the header file into the source file, so it really is the same as just typing their declarations (but not their definitions!)

As an aside, the difference between `#include <file>` and `#include "file"` is that the <> syntax first looks in your system include path like `/usr/include` or `/usr/local/include`, while the "" syntax looks first in your project directory.  Different compilers actually do different things if it can't find it in the first place it looks.  Some compilers will look in your project directory if you use <>, but most won't.  Same goes for "".  Best to just use the right syntax up front depending on whether you know you're using a system library or another component of your program.  In this case, the distinction is clear, and it communicates that to a savvy reader.

How do we compile such a program?  There are two ways:

First, we could do something similar to our `hello` example:
```
> gcc -o main main.c simple_math.c
```
The only difference is that we pass two source files to the compiler, instead of one.

Running this does what you'd expect:
```
> ./main
5 + 2: 7
3 * 7: 21
```

But there's another way, which uses separate compilation.  The way we did it above doesn't use separate compilation at all.  We called the compiler once, essentially passing it the entire program.  If our program gets large, it can start taking a while to compile all that source every time you make a minor change.

```
> gcc -c simple_math.c
> gcc -c main.c
> gcc -o main simple_math.o main.o
```

This breaks up the job into discrete steps.  First we compile the `simple_math.c` library.  Using the `-c` option tells the compiler to, well... compile.  When the compiler runs this way, it leaves behind an artifact called an 'object file', which is named the same as the source file, but with a `.o` extension.

Then we compile `main.c` and produce `main.o` the same way.

Then we do something new:  we 'link' the program together, without compiling at all.  We took the `.o` files and produced an executable.

So, I just lied.  I said we did something new.  Actually, we were linking in our original example, too.  We just compiled and linked all in one step, so it was transparent.  Linking basically hooks up 'uses' with 'definitions'.  What about declarations?  Declarations are really only used during the compiling step.  However, I did just say that 'uses' are used by the linker, so what does that mean?

Let's make this really concrete, and break out a new tool: `nm`

```
> nm simple_math.o
0000000000000048 s EH_frame0
0000000000000000 T _add
0000000000000060 S _add.eh
0000000000000020 T _multiply
0000000000000090 S _multiply.eh
```

Cool.  `nm` is short for 'name'.  Srsly?  We had to shorten the word 'name'?

Anyway, this program reads object files and tells you what's in them.  Object files are just raw bytes, with enough minimal format to tell the linker and other tools what those bytes are.

Ignore the `EH_frame0` and the lines that end with `.eh`.  That's an old Mac thing.  What we see is that this this object file contains definitions for `_add` and `_multiply`, just like we'd expect.  The number indicates the offset address within the object file where the definition is located.  The `T` means that data is intended to be located into the "text" section.  It's a horrible name, but "text" means read-only data, and in this context it actually refers to read-only executable code.  That's right.  We'll see examples of other sections later.

What about `main.o`?

```
> nm main.o
0000000000000090 s EH_frame0
0000000000000076 s L_.str
0000000000000081 s L_.str1
                 U _add
0000000000000000 T _main
00000000000000a8 S _main.eh
                 U _multiply
                 U _printf
```

Well, this defines `_main` in the "text" section, just like we'd expect, as well as some other stuff.
But look closely, it has `_add`, `_multiply`, and even `_printf` there with a `U`.  `U` means "undefined", which means it was 'used' but not 'defined' in this object file.  Perfect!

When the linker runs, it links up the undefined uses of `_add` and `_multiply` in `main.o` with the definitions of those same symbols in `simple_math.o`.

Each of these little entries that actually define something (as opposed to the ones that have no address, and are marked with a `U`) is just a raw sequence of bytes.  For executable code, the bytes are the actual instructions that will be executed by your CPU.  They just haven't been put in the right place yet.  Linking is the process of moving those bytes around, and doing just enough patching of the numbers within those bytes, so that they point to each other.

Let's go a bit more advanced, and look at `main` itself:

```
> nm main
0000000100001048 S _NXArgc
0000000100001050 S _NXArgv
0000000100001060 S ___progname
0000000100000000 T __mh_execute_header
0000000100000e60 T _add
0000000100001058 S _environ
                 U _exit
0000000100000dd0 T _main
0000000100000e80 T _multiply
                 U _printf
0000000100001000 s _pvars
                 U dyld_stub_binder
0000000100000d90 T start
```

`_main`, `_add`, and `_multiply` are all there and defined in the text section.  Excellent.  What this means is that the instructions in `_main` are actually referring to the real addresses of `_add` and `_multiply`.  What addresses are those?  Well, looks like `100000e60` and `100000e80`, respectively.  Those are the actual virtual addresses that will be used when you run the program.  I say virtual, because modern OSes have a layer of indirection between the addresses your program uses and the actual physical addresses that data is stored in.  But we'll have to discuss virtual memory and MMUs another time.  If you were running on a really small microcontroller, these would be the physical addresses that you burn into your EEPROM or whatever.  Modern OSes kind of simulate that idea, and try their hardest to let each program operate like it has the entire computer all to itself, full memory address space and all.

But wait.  WTF?  `printf` is still undefined!?

Now we're really getting a bit out of C per se, but this is still part of the cultural landscape, so let's explore it a bit.
On a Mac, there's a system called `dyld`, which is short for "dynamic loader" or "dynamic linker".  Basically, linking `printf` will be done at the start of your program, rather than right now.  Why is that?  Well, there's a good reason.  We don't want multiple definitions of `printf` and all of its dependencies copied all over the memory of your computer.  It's just too common.  If everyone statically linked, rather than dynamically linked, then every program would contain a copy of all of its dependencies, all the way down, and would actually load that copy into memory when it ran.  80% of of your memory would be redundant.  Dynamically linking lets your OS do the stitching up of common things at runtime rather than at build time, which has lots of little benefits, like cache locality, I/O optimization, and so forth.  Anytime you see a file that ends in `.dylib`, or `.so`, or `.dll`, that's what those are:  libraries that are designed to be linked at runtime, rather than statically at build time.  They're just like `.o` files, but they have extra stuff in them that works with the OS.  Unfortunately, that also means they're very OS-specific, so the details are quite different across computers.

Anyway, enough of that.  There's tons of stuff to know about how dynamic linking and loading actually works, but thankfully, you don't really have to know about it too much to use C and the various libraries that come with your computer.

I told you I'd talk about those `#ifndef` macros.  Let's cover that with some more C examples in the next lesson.
