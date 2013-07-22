## separate-compilation

Separate compilation is an important concept in C.  It lets you compile less than all of your code when you make incremental changes to source files.  It's also used for precompiling libraries, and then not having to recompile them just because you changed your program.

It's related to a deep idea in computer science:  separate the things that change from the things that don't.

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
