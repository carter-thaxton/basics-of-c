 It can also produce a `.a` file, which is basically just a tar of `.o` files, but with all of the interdependencies already linked up.  It's a library, instead of an executable.  Other software can then use `.a` files as a library that they "statically link" into their programs, just as though they were part of that program all along, and linked in all of the individual `.o` files.  Static linking

(and also `.a` files, which we'll discuss later), and produces an executable.


There's a related rule called the *One Definition Rule*.  You can declare something many times, but you may only define something once.  This is because declarations merely let the compiler know about something that is may use later.  Whereas, a definition actually instantiates something.

Make sense?  No, of course it doesn't yet, but it will soon.  It's actually really simple.  Just need to see some more examples, and you'll get the aha.
