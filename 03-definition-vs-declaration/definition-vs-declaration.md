definition-vs-declaration
=========================

#### data.h
```
#ifndef DATA_H
#define DATA_H

extern int counter;
extern const char *title;

#endif
```

#### data.c
```
int counter = 6;
const char *title = "Welcome!";
```

#### main.c
```
#include <stdio.h>
#include "data.h"

int main(int argc, char *argv[]) {
  counter++;

  printf("counter: %d\ntitle: %s\n", counter, title);

  return 0;
}
```

#### at command line
```
> gcc -c data.c
> gcc -c main.c
> gcc -o main main.o data.o

> ./main
counter: 7
title: Welcome!

> nm data.o
0000000000000010 s L_.str
0000000000000000 D _counter
0000000000000008 D _title

> nm main.o
0000000000000078 s EH_frame0
0000000000000060 s L_.str
0000000000000004 C _counter
0000000000000000 T _main
0000000000000090 S _main.eh
                 U _printf
0000000000000008 C _title
```
