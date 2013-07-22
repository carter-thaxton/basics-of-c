
## hello

```
#include <stdio.h>

int main(int argc, char *argv[]) {
  printf("Hello, world!\n");
  return 0;
}
```

```
> gcc -o hello hello.c
> ./hello
Hello, world!
> echo $?
0
```


Let's take a look at each line of this entire incantation:


```
#include <stdio.h>
```
This is a preprocessor macro.  All lines that begin with `#` are preprocessor macros.  The preprocessor runs before the compiler sees any source code.  These days the preprocessor is built into the compiler, but they used to be separate programs.  So, you can just think of the preprocessor as a separate phase that runs before the parsing and compilation step.  The preprocessor itself is pretty dumb, and because it runs before the parser, it doesn't actually know how to interpret your source code.  Peprocessors are a necessary evil when working with C code.  We will use it in a very standard, acceptable way.

The `#include` macro inlines an entire copy of `/usr/include/stdio.h` into the source file.  It aworks recursively.  Your local copy of `stdio.h` itself has `#include` macros, so those get inlined, too.  By the time the compiler sees any of your code at all, it's already parsed an entire tree of header files, and then it parses your four lines.


```
int main(int argc, char *argv[]) {
```
This is a declaration of a function, and a definition, all in one line.  We'll get to the distinction later.  The function is named `main`.  It returns an `int`.  It accepts two parameters:  an `int` called `argc`, and a pointer to an array of `char`s called `argv`.  There's more to say about where to put the * and [], but we'll get to that later.

An `int` is a signed integer, but its size is actually not exactly specified by the C standard.  It's typically 32-bits these days, but on small little microcontrollers, it can be 16 bits.

These names are standard.  `argc` means "argument count".  `argv` means "argument vector".  Every few years, and even in other programming cultures, someone tries to rename the ubiquitous `argv` to `args`, because that would just make sense, but it never catches on.  `main` is a special function name.  If you name a function `main`, it will be the first thing in your program that gets executed.

The open brace at the end of the line means we are starting the function definition.


```
printf("Hello, world!\n");
```
This is a statement, which consists of a call to a function named `printf`.  It's passing a single string argument, with a constant value: "Hello, world!\n".

Strings in C are a whole subject in themselves.  The basics, however, are pretty straightforward.  Literal strings (in other words, ones you explicitly write out in your source code, as opposed to ones you read in from a file at runtime or something), are simply enclosed in double-quotes.  Single-quotes mean just one character in C, so we don't use those for whole strings.  Some special escaped characters are allowed in C string literals, such as '\n', which means a newline.  Let's not digress here into '\n' vs '\r' and all that.  Suffice it to say that unfortunately, some operating systems have different newline characters than others.  '\n' has an actual value of 10.

The other characters in the string also have integer values, using an encoding called ASCII.  In ASCII, upper-case 'A' is 65, lower-case 'a' is 97, a single space is 32, exclamation point is 33, and so forth.  So "Hello, world!\n" is actually an array of bytes:
  `[72, 101, 108, 108, 111, 44, 32, 119, 111, 114, 108, 100, 33, 10, 0]`.

Note that the array ends with a zero.  That's called the NUL terminator (which is technically not to be confused with the term "null pointer", but they're really just both special zero values, with different purposes).  In C, strings are typically NUL-terminated.  The length of the string is not actually stored anywhere automatically.  The string is not an object, with a method like `.length` or anything like that.  It's literally just an array of bytes in memory.  Nothing more.  Without the NUL, there'd be no good way to figure out where it ends.  Not storing the length along with the string is one of those "mistakes" that the developers of C greatly regret

It's worth pointing out that every statement in C ends with a semicolon.  Deal with it.  Whitespace is almost completely ignored, except to keep words apart like `int main`, and whether you use a space or a tab or a newline for whitespace doesn't matter at all to the compiler.  The only thing that keeps the statements apart is the semicolon.


```
return 0;
```
This is another statement, which returns a value from the function.  The value must match the declaration.  If you try to return a `string`, for example, but you declared the function to return an `int`, you'll get a warning.  (Yep, a warning, not an error.  Because technically a string is a pointer to an array of chars and pointers can be treated as int values, so the address of the first byte in the array of chars will be the int value that you get.  Try it!)

The value you return from `main` is important.  This is called the "exit status" of the program, and it's usually used to indicate success vs failure.  Success is indicated by a zero, and any other value indicates failure.  The exit status is a single byte, which has a range of 0-255.  There's not really a standard for what exit status values means what, other than zero vs non-zero.


```
}
```
This ends the function definition, and the program.


```
> gcc -o hello hello.c
```
Now let's look at how we compile and run our program.  Assume I saved the above program into a file called `hello.c`.  Then I open up the terminal, cd into the directory where I saved the file, and type that line at the prompt.  GCC means "GNU C Compiler", and it comes with most UNIX systems these days.  Learn about it, and love it.  Richard Stallman, say what you like about the guy, has done the world a favor, and supplied everyone with a free open-source compiler that comes with almost every computer system you will develop on.  It's available on Windows, too, of course.  Just gotta go get cygwin or whatever.  I'm going to just assume you have gcc already.  If not, stop what you're doing and go get it.  That's more important than this anyway.

If successful, nothing at all happens when you type that command.  You just see the next prompt.  That's a UNIX-ism.  Success is completely silent.  Errors occur early and loudly.

`-o hello` indicates that the output of the compiler should be saved as `hello`.  No extension or anything.  It will be the executable program itself.  The last argument(s) are the source file(s) to compile and link.  We'll get into the nuances of compiling and linking later.


```
> ./hello
```
You should now have an executable file called simply `hello`.  Let's run it.  Using "./" runs the file that's right here in this directory.  If you just type `hello` it might not work, unless "." is on your PATH (which it probably shouldn't be, for various security reasons).


```
Hello, world!
```
Yay!  The output of our program.  It worked.  Newline and all.  If we left out the newline from the string we passed to printf, then the next prompt wouldn't even be on its own line.


```
> echo $?
```
This is a cool way to inspect the exit status of our program.  `$?` is a special shell variable (like `$PATH`) that your shell keeps around to indicate the last exit status.


```
0
```
Yup, that's what we returned.  Success!
Incidentally, if you type `echo $?` again, you'll get the exit status of the previous execution of the `echo` command, which is probably still zero, because it worked, but it's not the "same" zero.

