A timeline of past and future versions.

### v4.2.1

Added error handling, runtime errors can be caught.

### v4.2.0

Added file handling.

### v4.1.2

Added modules, similar to Python's modules.

### v4.1.1

Added enumerations, but not like Java's weird enums, they're more like C's enums.

### v4.1.0

Added classes. However they can only contain variables and methods, no inheritance, visibility, etc. So think of them as C structs

### v4.0.1

There are now compile time checks for expressions in functions! Another big step in improving safety.

### v4.0.0

The first actual good version of Night!

This version turns Night into a dynamically typed language, with the `set` keyword used to create a variable, and the `def` keyword for functions. Also removed semicolons and made curly braces in conditionals and loops optional if there's only one statement.

There's also compile time checks to see if variables and functions exist, if functions have the right number of parameters, and expressions. This should catch a lot of hidden runtime bugs and make the code way more stable. (take that Python!)

And we're also back to using C++'s STL instead my own. And the entire parser and interpreter system is reworked. We now have an actual parser that constructs an AST and all that stuff.

## Version 4

A complete rewrite focused on making the langauge dynamically typed, and adding useful syntax like array slicing, in addition to adding core features like classes and file handling.

- `v4.0` will mainly focus on making the language safe and scalable
- `v4.1` will be focuses around encapsulation
- `v4.2` will be adding utilities like file and error handling
- `v4.3` networking??

### v3.2

Added compatability with the standard library and the package manager.

### v3.1

Functions could now return arrays and accept them as parameters.

### v3.0.1

Fixed a small bug with source builds for Linux.

### v3.0.0

The first non-beta version of Night! (it's still so bad though)

Changed how expressions are evaluated, making it more efficient. Also created my own string and vector class (why? idk don't ask me).

## Version 3

This version was intended to be a "testing" release, with many new features testing and implemented here.

### v2.4-beta

Added user input in the form a function.

### v2.3-beta

Added flexible arrays that can be reassigned to other arrays.

### v2.2-beta

Added a simple loop that would iterate a set amount of times.

### v2.1-beta

Added more support for expressions, along with assignment operators like `+=` and `*=`.

### v2.0-beta

The base release for Version 2.

Turned the `print` keyword into a function.

Also made the code more modular and just better in general, especially when it came to the interpreter. And I made an actual Error class.

## Version 2 Beta

### v1.0-beta

The first version of Night! (the code is so bad plz don't look at it)

It supported 5 basic types, bools, chars, ints, floats, and strings. It also supported variables, expressions, conditionals, and functions, along with a `print` keyword.

Not bad for the first verison actually, considering that I didn't even know the difference between an interpreted and compiled language :/

## Version 1 Beta