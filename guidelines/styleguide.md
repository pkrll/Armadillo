# Style guide for Project Iota / Uphill

*Author: Ardalan Samimi*<br>
*Version: 1.0.0*

This document outlines the coding conventions for Uphill and should serve as a guide for writing consistent, concise and readable code in **C**.

This is a short summary of the Google C/C++ style guide. For more information, read the [guide](https://google.github.io/styleguide/cppguide.html).

This is a dynamic document. As it will be subject to change, it is important to check in here from time to time.

## Table of Contents
* [Astyle](#astyle)
* [Formatting](#formatting)
  * [General formatting rules](#general-formatting-rules)
  * [Functions](#functions)
  * [Conditionals and loops](#conditionals-and-loops)
  * [Switch statements](#switch-statements)
  * [Pointer and Reference Expressions](#pointer-and-reference-expressions)
* [Naming conventions](#naming-conventions)
  * [General rules for naming](#general-rules-for-naming)
  * [Variable names](#variable-names)
  * [Type names](#type-names)
  * [Function names](#function-names)
  * [Enum values and macros](#enum-values-and-macros)
  * [Constants](#constants)
* [Remarks](#remarks)

---

## Astyle

Always format the code using the command line tool ``astyle`` before committing your code. This can be done just by writing ``make style`` in the root folder of the project.

**Note:** Keep in mind  that the tool only fixes formatting stuff, and not for example variable or function names.

---

## Formatting

Presentation matters, and a lot of the times we (humans) forget that. So, let's begin with the formatting rules.

### General formatting rules

*Some of these rules should be handled by your editor automatically, if it supports the [Editor config plugin](http://editorconfig.org/#download), otherwise you may need to manually change the configurations.*

* Tabs are used for indentation. No spaces.
* All files must end with a newline.
* Don't add a space after an opening parenthesis ``(`` or before a closing parenthesis ``)``:

```c
int foo = 3 * (15 / (1 + 2));
```

### Functions

* A function's return type and name should be placed on the same line, along with its parameter list (if it fits, otherwise see below).

* The opening curly brace ``{`` should be placed on the same line as the parameters (or, in case of long parameter lists, on the same line as the last parameter). After all, we are not barbarians.

* There should not be a space between the opening parenthesis ``(`` and the function name, but there should be a space between the closing parenthesis ``)`` and the opening curly brace ``{``.

```c
void foo(int x) {
  ...
}
```

* For readability reasons, it is allowed to wrap the parameter list. If the function name is really long, you can even put each of the parameters on a new line, with two tabs.

```c
bool foo(int parameter1, int parameter2, int parameter3,
         int parameter4, int parameter5) {
  ...
  return false;
}

bool foo_bar_deluxe_with_a_really_long_name(
    int parameter1,
    int parameter2,
    int parameter3,
    int parameter4,
    int parameter5) {
  ...
  return false;
}
```

* Function calls should be indented the same way as function definitions, described above.

### Conditionals and loops

* The ``if`` and ``else`` keywords belong on separate lines.

* Do not put spaces between the parenthesis.

* Put a space before the ``if`` keyword and opening parenthesis ``(``, and also after the closing parenthesis ``)``.

```c
if (condition) {  // no spaces inside parentheses
  ...
} else if (...) {  // The else goes on the same
  ...              // line as the closing brace.
} else {
  ...
}
```

* The Google standard doesn't require curly braces for single-line conditional statements or loops, but for readability and maintainability reasons **Iota** should always put curly braces on ``if``-statements and loops.

```c
if (condition) {            while (condition) {
  statement                   statement
}                           }
```

* **But**, if it helps readability, ``if``-statements may be written on one line. You may use this only when the line is brief and the statement does not use the ``else`` clause.

```c
if (condition) return something;
```

### Switch statements

* The ``case`` blocks in a ``switch`` statement should be put on separate lines, with a single indent. The body of code following it should have a double indentation, aligned with the ``break`` keyword.

* The ``default`` clause is required for statements that are not conditional on an enumerated value, as the compiler otherwise will warn you that the ``switch`` statement is not exhaustive.

```c
switch (foo) {
  case 'bar':
    ...
    break;

  .
  .
  .

  default:
    ...
    break;
}
```

### Pointer and Reference Expressions

* Place the ``*`` attached to the variable name, making it super clear that we're working with a pointer.

```c
char *foo  = ... // Do this
char* foo  = ... // NOT this
char * foo = ... // NOT this
```

---

## Naming conventions
Naming stuff is important. It makes it easier for us to read and understand our own and someone else's code. This includes both what we name them (what does ``int x`` or ``char *foo`` signify?), but also how we format it.

### General rules for naming

* Names should be descriptive, avoid abbreviations. It should be clear what a function does, or what a variable holds without having to read the entire code.

* The longer the scope, the more descriptive should the name be. For instance, a loop variable may be named ``i`` as it is used only inside the loop, and from the context it is clear what it means. But a global variable named ``x`` does not say anything.

```c
int x = 0; // Not OK

void foo() {
  for (int i = 0, i < 10; i++) { // This is OK
    ...
  }
}
```

### Variable names

* The names of variables (including function parameters) and struct members are all lowercase, with underscores between words (snake case).

```c
char *shelf_name;
int number_of_items;
bool shelf_is_empty;
```

### Type names

* The names of all types — structs, type aliases and enums — have the same naming convention. Type names should start with a capital letter and have a capital letter for each new word. No underscores.

* Furthermore, ``typedef`` names should end with a ``_t``.

```c
enum ShelfOptions {
  ...
}

struct Record {
  ...
} typedef Record_t;
```

### Function names

* Functions should be named like variables (snake case), even though the Google standard uses Pascal case for naming functions. This avoids lowering the readability for team members that may not be familiar with this naming convention.

```c
void foo();
void some_function();
```

* Function names should be descriptive. The name should reflect what the function does.

* Take advantage of the function signature, meaning you can omit some words if it is clear from the context what it does.

```c
// This is OK
void add_to_database(Item_t *item, Database_t *database);
// This may be too verbose
void add_item_to_database(Item_t *item, Database_t *database);
```

### Enum values and macros

* Enum values and macros should be named with all capitals and underscores:

```c
#define MAXIMUM_ITEMS 20

enum FileOptions {
  OPEN, CLOSE, READ_WRITE
};
```

### Constants

* Constants are named with a leading ``k`` followed by camel case, for example: ``kMaximumItems``.

---

## Remarks

* As always, style and conventions are (almost always) arbitrary and only a matter of taste. If you come across a case that's not covered by the Google style guide, be consistent in your own code with your choices (and communicate with your team mates).
