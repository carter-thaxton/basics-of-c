## intro

The great thing about learning any language is that you mostly learn the "culture" in and around the language.  The syntax and even deep semantic structure are not what is important.  Rather, it's the context in which the language thrives that is most interesting.  This is why most educators agree that the best way to learn a language is by immersion.

It's also why "how" you travel is so important.  You must be open to other ways of living.  If you don't come home changed, you didn't really travel.  You just "did" Europe or whatever.  You won't learn a language by "doing" a country.  If you really prefer that terminology:  it has to "do" you.

Computer languages are no different.  When you learn Javascript, you're mostly learning about browsers and the web.  Learning Java will teach you about object-oriented paradigms and how to structure large programs that run in a garbage-collected virtual machine.  Perl has its place in practical UNIX scripting.  Ruby and Python have their roots in scripting languages like Perl, but also embrace object-orientation, which is useful for larger, longer-running programs than simple scripts.

Users of Haskell and Ocaml prefer the academic purity of exploration of functional ideas to actually gettings things done.  Seriously.  To learn Haskell is to explore ideas.  You don't learn Haskell to get things done.  You learn Haskell to gain deeper insight into how things get done.  Nobody who seriously works on Haskell actually uses it for day-to-day scripting.  Haskell is the most important language you will never use.  Learn it.

Similarly, Lisp dialects are explorations of expressivity.  Clojure is an interesting intersection of the practical Java world, the expressive functional concepts of Lisp, and some parallel STM stuff to boot.  But I digress.

Each of these languages is much more than a collection of syntax.  It's a whole ecosystem of users, forums, libraries, package managers, build systems, and development environments, (or lack thereof).  The language culture also has an opinion on interoperability with other programming cultures.  .NET has built-in interoperability with the whole binary DLL culture of Windows, but doesn't play well with Java at all.  Java's opinion is that you shouldn't use any other programming language.  It's now acceptable to at least live on the same VM continent, and use Scala or Clojure, but it's still a very xenophobic culture.  Is that bad?  Not necessarily.  Java has its place, and luckily, its proponents will tell you why, so I don't have to.

Programming cultures reflect the times and context of their development.  The Web and the Internet have fueled the growth of shared libraries and communities around programming languages, and only enrichened the corresponding cultures.  New languages developed since the Web and Github became commonplace have a different feel to them.  Using Node.js is particularly fresh, because it does two things very well:  embraces the web and its culture, and also bridges to UNIX and its culture of good fundamentals.

C is a language.  It's also a culture.  I'd like to share what I know of this culture.  I've lived in C-land for many years, and I like to think I speak the C equivalent of American Broadcast English, which lacks any obvious regional dialect.  I also speak C++, and I use a simplified version of it, sort of like Simplified Chinese.  That means anything I say here should be relatively nonconfrontational, and should get plenty of nods from a similarly-educated audience, rather than raised eyebrows.

The good fundamentals of UNIX have been written about many times.  The fact that Node.js embraces those fundamentals has also been a common theme recently.  However, UNIX is also tied up with C.  UNIX is our Rome, and C is its Latin.  All good programmers should know it.  One day we may move on, but programming is still in its infancy, and it behooves us to understand and embrace our shared cultural roots.

Let's get to it.
