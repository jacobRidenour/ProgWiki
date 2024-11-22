# C

The C programming language features ahead of time (AOT) compilation, and supports procedural (imperative) programming. Its type system is static, manifest, and nominal.

Function parameters are passed by value (copied), except for arrays, which are passed as pointers.

C has been standardized since 1989. The content in this folder will reflect C from ANSI C (1989) up through the features included in the 2017 standard, C17.

C is essentially an abstraction of assembly.

There are 3 related categories of behavior to watch out for with C (and C++) that can cause unintuitive bugs (definitions adapted from [here](https://stackoverflow.com/questions/2397984/undefined-unspecified-and-implementation-defined-behavior) and [here](https://en.cppreference.com/w/c/language/behavior)):

* **Implementation-defined behavior**: behavior, for a well-formed program construct and correct data, that depends on the implementation and that each implementation documents
   * Examples: order of operand evaluation for the operator `+`. The size of `int`. In-memory order of the bits in a byte (endianness)
* **Undefined behavior**: behavior for which \[the standard\] imposes no requirements
   * Examples: dereferencing a `NULL` pointer, modifying a string literal, indexing outside the boundaries of an array, division by 0
* **Unspecified behavior**: behavior, for a well-formed program construct and correct data, that depends on the implementation; in C, the standard provides 2 or more possibilities and imposes no prescription on which is chosen
   * Examples: order of evaluation for function arguments

---
---


- [Creating a Binary](#creating-a-binary)
  - [Preprocessor](#preprocessor)
    - [#include](#include)
    - [Conditional Compilation](#conditional-compilation)
    - [Macros](#macros)
  - [Compilation \& Assembly](#compilation--assembly)
  - [Linker](#linker)
- [Objects](#objects)
- [Expressions](#expressions)
  - [Types](#types)
  - [Values](#values)
- [Storage-Class Specifiers](#storage-class-specifiers)
- [Type Qualifiers](#type-qualifiers)
- [Alignment](#alignment)
- [Operator Precedence \& Associativity](#operator-precedence--associativity)
- [Memory Layout](#memory-layout)
- [Memory Management](#memory-management)
  - [Checking for Memory Leaks / Memory Corruption](#checking-for-memory-leaks--memory-corruption)
    - [Windows](#windows)
    - [Linux](#linux)
- [Attribute Specifier Sequence](#attribute-specifier-sequence)
  - [Details on unsequenced and reproducible](#details-on-unsequenced-and-reproducible)
- [Assertions](#assertions)
- [VS Code Setup](#vs-code-setup)
  - [Windows](#windows-1)
  - [Linux](#linux-1)
- [Build Systems](#build-systems)
- [External Libraries](#external-libraries)
- [Using the Debugger](#using-the-debugger)

---
---

## Creating a Binary

There are 3 main programs involved in creating a binary, such as an executable, from C source code.

They are:  
* the preprocessor,
* the compiler, and
* the linker.

When we build a C program, all three of these steps occur sequentially by default.

Any references to compiler flags here are referring to the GNU C compiler `gcc`.
![Compilation process for C.](../__images/compilation-c.png)

### Preprocessor
---

The [C preprocessor](https://gcc.gnu.org/onlinedocs/gcc-2.95.3/cpp_1.html) is a fancy text replacement machine. The preprocessor is what replaces all of your `// single line comments` and `/* multi-line comments */` with whitespace.

Lines that start with `#` invoke preprocessing directives. The most common uses are to make the contents of header files available in a source file, conditional compilation, and macros. Directives may be cosmetically split into multiple lines by ending a line with `\\n`. The preprocessor removes these to put everything on one line.

The (normally temporary) files output by the preprocessor usually have the `.i` extension and are known as **translation units** or **compilation units**.

#### #include

There are a number of header (`.h`) files provided by your operating system containing functions for basic tasks, such as opening files or printing to the screen. Header files contain **declarations** of functions.

When used to make header files available, the `#include` preprocessing directive is more or less equivalent to copying that file's contents into a copy of the current file, once complete.

`#include <file>` starts the search for files in the directories specified by the `-I` flag in your call to gcc, then in the standard OS directories, while `#include "file.h"` starts the search in the current directory, then in the standard OS directories.

#### Conditional Compilation

The most common usage of conditional compilation is with header guards.

In C (and C++), multiple `#include` directives for the same file will include it over and over again; besides wasting time, if a function or a type is defined more than once, a compilation error will occur, because there is ambiguity about which copy of a function, type, etc. to call. With a header guard, we create a parameterless macro that prevents the header file from being included more than once.

```C
#ifndef MyHeader_H
#define MyHeader_H

// header file contents

#endif /* MyHeader_H */
```

The header guard is a big `if` statement; if we haven't included this file before (`MyHeader_H` is not defined), we will include it, otherwise do nothing. Most C preprocessors will also support the directive `#pragma`. If yours does, you can simply put `#pragma once` before your header file's code. This will act identically to the header guard in most cases.

Another common usage is for functions that are defined in different headers on different operating systems: 

```C
#ifdef _WIN32
#include <windows.h>
#endif

#if defined(__linux__) || defined(__unix__)
#include <unistd.h>
#endif
```

It can also be used to provoke different behavior only if doing a Debug build, relative to a Release (optimized) build:

```C
int sum(int a, int b) {
    int total = a + b;

#ifdef _DEBUG
    printf("Debug: a = %d, b = %d, a + b = %d\n", a, b, sum);
#endif

    return total;
}
```

C Comments do not nest, if you need to keep commented out code for reference you can simply wrap it in `#if 0 ... #endif`

#### Macros

Macros are convenient abbreviations capable of black magic. Header guards are an example of a macro with no parameters, but they may have parameters. By convention, their names are in all caps. The preprocessor replacing the macro name with its definition is known as macro expansion. Note that macro expansion happens after comments are replaced with whitespace.

They are sometimes used to define constants, and after expansion and usage, they are checked for references to other macros. 

```C
#define BUFFER_SIZE 100
#define N_ELEMENTS BUFFER_SIZE
#define min(X, Y)  ((X) < (Y) ? (X) : (Y))
#undef N_ELEMENTS
```

It is best practice to put parentheses around each argument to a macro to prevent unintended behavior.

```C
#define ceil_div(x, y) (x + y - 1) / y
// expands to:   (x & y + sizeof (int) - 1) / sizeof (int);
// precedence:   (x & (y + sizeof (int) - 1)) / sizeof (int);
// but we want:  ((x & y) + sizeof (int) - 1)) / sizeof (int);
#define ceil_div(x, y) (((x) + (y) - 1) / (y))
/* correct behavior; wrapping in parentheses prevents unintended behavior
when doing something with the result of the macro, e.g. sizeof(ceil(x, y)) */
```

Refer to the GNU page on the C preprocessor for more preprocessor directives.

### Compilation & Assembly
---

The `.i` files (compilation units) produced by the preprocessor are used as input to the compiler. This effectively means each `.c` file becomes an independent compilation unit.

All functions used in a compilation unit must be **declared** (as is typically done in `.h` files). 

The compiler first checks that the source code follows the syntax, semantics, and grammar of C (lexical analysis, parsing). Next, the source code is converted into an intermediate representation (**IR**). For gcc, this IR is called GENERIC.

GENERIC is a language-independent way of representing a function as a tree. From here, the GENERIC expressions are broken down into tuples with (mostly) up to 3 operands; this IR is called GIMPLE. For C/C++, the compiler converts directly to GIMPLE with no GENERIC intermediary. The GIMPLE is then used as input to the optimizer.

The optimizer's goal is to improve code's performance and size. As a consequence of this, compile times increase. There are several optimizer (`-O{#}`) flags that can be passed in, which are themselves (mostly) shorthand for a number of optimizer flags. `-O0` is the default and makes debugging behave as expected. The `-g` argument will generate debug info. The optimizer outputs optimized GIMPLE.

The optimized GIMPLE is converted into another IR called register transfer language (RTL), a lower-level representation that (mostly) generically describes how the hardware register operations occur. Another optimization is done on the RTL, which is generally platform specific and has a tighter scope than the previous higher level optimizations.

Then, assembly code for each compilation unit is generated from the RTL, taking into account target-specific properties such as the number and types of registers. The resulting `.s` files are used as input into the assembler `as`, which produces object files (`.o`) containing machine code for each compilation unit. Object files may contain local symbols, which are used internally to ease relocation by the linker, undefined external symbols (references to other modules where those symbols are defined), and defined external symbols, which allow the object file to be called by other modules.

### Linker
---

The last step in the process is to combine our object files together with the linker `ld`. There are two types of linkage for functions, internal and external. Only those with external linkage (the default) are visible to the linker; static functions have internal linkage and are only visible inside the compilation unit they're defined in. The output of the linker is a binary file that may be an executable (`.exe`), a static library (`.lib`, `.a`), or a shared library (`.dll`, `.so`).

The linker's first job is symbol resolution. Each symbol (i.e. function, variable) that is used needs to have its **definition** found exactly once in one of the object files. Once found, each reference is replaced with the definition.

Some symbols that are used may be defined in existing library files. If they are static libraries, the referenced symbols are copied directly into the output binary. Resolution of some symbols may be deferred until runtime (dynamic linking); in this case, the binary will contain undefined symbols, plus a list of libraries that contain definitions for these symbols.

The final addresses of the blocks (code, data) in object files are not known at generation time, so they usually assume an address base of 0. The linker relocates and adjusts these addresses to avoid overlaps.

For more practical information on compiling C projects, refer to [C Compilation](COMPILATION_C.md).

## Objects

C is not an object-oriented language, but the standard and reference pages frequently refer to `objects`, which are regions of data storage in a program - your typical variables - which have a number of attributes:

* size (get with `sizeof` operator)
* alignment requirement (get with `alignof` operator)
* storage duration (automatic, static, dynamically allocated, thread-local)
* lifetime (same as storage duration or temporary)
* effective type<sup>†</sup>
* value<sup>†</sup>
* identifier (optional)

<sup>†</sup> See Expressions

## Expressions

Expressions have 2 independent properties: a [Type](https://en.cppreference.com/w/c/language/type) and a [Value](https://en.cppreference.com/w/c/language/value_category).

### Types

* Unspecified type: `void`
* Basic types
  * `char`
  * Signed integers
    * Standard: `signed char`, `short`, `int`, `long`
       * `long long`<sub>(C99)</sub>
    * Bit-precise<sub>(C23)</sub>: `_BitInt(N)` (includes sign bit)
  * Unsigned integers
    * Standard: `_Bool`<sub>(C99)</sub>, `unsigned char`, `unsigned short`, `unsigned int`, `unsigned long`
      * `unsigned long long`<sub>(C99)</sub>
  * Floating-point types
    * real types: `float`, `double`, `long double`
    * real decimal types<sub>(C23)</sub>: `_Decimal32`, `_Decimal64`, `_Decimal128`
    * complex types<sub>(C99)</sub>: `float _Complex`, `double _Complex`, `long double _Complex`
    * imaginary types<sub>(C99)</sub>: `float _Imaginary`, `double _Imaginary`, `long double _Imaginary`
  * Enumerations (originally int only, any integral type as of C23)
  * Derived types
    * Aggregate types
      * Array types
      * Structure (`struct`) types
    * `union` types
    * Function Types
    * Pointer types
    * Atomic types<sub>(C11)</sub>

Types may be aliased using `typedef type alias` and scoped as desired.

### Values

* **lvalue**
  * So-called because these were on the left-hand side of the assignment operator in CPL; not necessarily true in C. Something that has a **l**ocation in memory.
  * Any expression with an object type (non-function type) besides void.
    * Behavior undefined if an lvalue is not an object type when evaluated
  * Examples
    * Identifiers
      * Includes function named parameters, if they were declared as designated objects and not functions/enums
    * String literals
    * Compound literals<sub>(C99)</sub>
    * `(expression)` if `expression` is an lvalue
    * Result of operators `->`, `[]`
    * Result of dereference `*` on pointer to object
    * Result of `.` if left-hand argument is an lvalue
  * Contexts
    * Left-hand operand of compound/assignment operators
    * Left-hand operand of `.` operator
    * Operand of `&` if the lvalue isn't a bit-field or declared a register
* **rvalue**
  * Aka non-lvalue object expressions; values with no object identity or storage location. No address can be taken.
  * Examples
    * integer, char, floating-point constants
    * Operators which don't return lvalues, including:
      * Function calls, casts
      * Dot operator used on non-lvalue struct/union
      * Results of arithmetic, relational, logical, bitwise operators
      * Results of increment/decrement operators<sup>†</sup>
      * Results of assignment operators<sup>†</sup>
      * Results of conditional operators<sup>†</sup>
      * Conditional operator, comma operator<sup>†</sup>
      * Address-of operator, even after dereferencing
* **function designator** - function declarations used in any context besides with the address-of operator

## Storage-Class Specifiers

Storage duration and linkage type specifier, used with types and functions

| Specifier | Storage Duration | Linkage | Scope | Lifetime | Notes | 
| --------- | ---------------- | ------- | ----- | -------- | ----- |
| `auto` | automatic | none | block | block execution | rarely used explicitly;<br>`auto` can also be used for type inference<sub>(C23)</sub> |
| `register` | automatic | none | block | block execution | address cannot be taken & can't use `alignas`;<br>hints to compiler that variable will be used heavily but (at least in `gcc`) has 0 effect on code generation |
| `static` | static | internal<br><sub>unless at block scope</sub> | file or block | program execution | value initialized only once, prior to `main()` |
| `extern` | static | external<br><sub>unless already declared internal</sub> | file or block | program execution | |
| `thread_local` | thread | static | none | thread | formerly known as `_Thread_local`;<br>each thread gets a copy of this object. |
| `constexpr`<sub>(C23)</sub> | static | same as declaration | block execution | N/A | specifies that object should be available during compilation;<br>object may not be modified at all during runtime;<br>may not be used with pointers, variably-modified types, or `_Atomic`, `volatile`, or `restrict` types |

File scope variables that are `const` but not `extern` have external linkage (default); internal linkage in C++.

## Type Qualifiers

| Qualifier | Effect | Notes | 
| --------- | ------ | ----- |
| `_Atomic`| the variable may be modified concurrently by multiple threads | size, alignment, and object representation may differ relative to other qualifiers |
| `const`| the variable may not be modified | applies to lvalue expressions only;<br>struct/union members inherit the qualifier |
| `volatile` | compiler will not cache the value of the variable | useful when the variable may be modified by hardware or another thread;<br>the compiler will not optimize anything associated with this variable  |
| `restrict`<sub>(C99)</sub> | this pointer is the only one that accesses the underlying object | applies to lvalue expressions only;<br>may only be used on a pointer-to an object type, or n-dimensional array<sub>(C23)</sub>;<br>worth considering for preventing [load-hit-stores](https://en.wikipedia.org/wiki/Load-Hit-Store) |

Type qualifiers may be combined. For instance, if you have hardware that writes to a variable, but your program should never modify it, you might declare it `const volatile`.

## Alignment

Alignment refers to the number of bytes between successive addresses for objects of this type; it must always be a (positive) power of 2. Types may have padding to meet alignment requirements. The smallest/weakest alignment, 1, applies to the types `un/signed/char`; the largest/strongest alignment is implementation-defined but equivalent to that of the type `max_align_t`<sub>(C11)</sub>, defined in `<stdalign.h>`. Objects may be given a larger (extended) alignment requirement if their compiler supports it.

Typical use cases for alignment are avoiding cache misses, false sharing for concurrently-accessed data, and meeting specific hardware requirements.

* `alignof(type)` (`_Alignof` before C23) returns the alignment requirement of the provided type.
* `alignas(type|expression)` (`_Alignas` before C23) set the alignment requirement of the provided type. 
  * `alignas` may not be used on struct declarations but may be used in member declarations.

## Operator Precedence & Associativity

Original (and possibly more up to date) reference: [cppreference: C Operator Precedence](https://en.cppreference.com/w/c/language/operator_precedence)


| Precedence | Operator | Description | Associativity |
| ---------- | -------- | ----------- | ------------- |
| 1  | `++` `--`<br>`()`<br>`[]`<br>`.`<br>`->`<br>`(type){list}` | Postfix increment/decrement<br>Function call<br>Array subscripting<br>Struct/union member access<br>Struct/union member access thru pointer<br>Compound literal<sub>(C99)</sub> | Left-to-Right |
| 2  | `++` `--`<br>`+` `-`<br>`!` `~`<br>`(type)`<br>`*`<br>`&`<br>`sizeof`<br>`_Alignof` | Prefix increment/decrement<br>Unary plus/minus<br>Logical NOT/bitwise NOT<br>Cast<br>Dereferebce<br>Address-of<br>Size-of<br>Alignment requirement<sub>(C11)</sub> | Right-to-left |
| 3<br>4<br>5<br>6<br>7<br>8<br>9<br>10<br>11<br>12 | `*` `/` `%`<br>`+` `-`<br>`<<` `>>`<br>`<` `<=` `>` `>=`<br>`==` `!=`<br>`&`<br>`^`<br>`\|`<br>`&&`<br>`\|\|` | Multiplication, division, remainder<br>Addition, subtraction<br>Bitwise left/right shift<br>Relational operators < ≤ > ≥<br>Relational = ≠<br>Bitwise AND<br>Bitwise XOR<br>Bitwise OR<br>Logical AND<br>Logical OR | Left-to-right |
| 13 | `?:` | Ternary conditional | Right-to-Left |
| 14 | `=`<br>`+=` `-=`<br> `*=` `/=` `%=`<br>`<<=` `>>=`<br>`&=` `^=` `\|=` | Assignment<br>Compound Assignment<br><br><br><br> | Right-to-Left |
| 15 | `,` | Comma | Left-to-right |

Gotcha: notice that logical AND is given higher precedence than logical OR; this probably originates from the operations * and +, but to be accurate boolean algebra, they should be given equal precedence.

`typeof` operators (`typeof` and `typof_unqual`) were added in C23. They provide the type name representing the type of the operand (a type or expression, like `sizeof`), not including any implicit conversions. It functions very similarly to `decltype` in C++ (but with a different name for compatibility's sake).

## Memory Layout

This section is generally applicable to other compiled languages; specifics may differ depending on language and operating system. The memory of an executable is divided into multiple named segments, with varying purposes.

| Segment | Data | Characteristics | Notes | 
| ------- | ---- | --------------- | ----- |
| Text Segment | machine code instructions | read-only, executable ||
| Data Segment | initialized global variables<br>initialized static variables | read-write | statically allocated data |
| BSS Segment | uninitialized global variables<br>uninitialized static variables | often initialized to 0 | statically allocated data;<br>stands for Block Started by Symbol |
| Stack Segment | stack frames | fixed size (sometimes adjustable);<br>now non-executable by default (security) ||
| Heap Segment | explicitly requested memory | whatever is requested; size/lifetime determined at runtime | dynamically allocated data |

Stack frames contain the function prologue/epilogue, parameters, local variables, and return address. 

The text of string literals is usually in the Text segment or a Read-Only-Data segment; varies by platform.

## Memory Management

Memory for stack variables (statically allocated) is taken care of by the compiler.

The programmer is responsible for managing the memory of heap variables (dynamically allocated). Generally, heap variables should be used cautiously, such as for variables where the lifetime should last beyond the current function. Free their memory within the same scope or function wherever possible; barring that, the same file (especially if your program is part of a library).

TODO: fill out more. Examples?


### Checking for Memory Leaks / Memory Corruption

#### Windows

TODO: fill out more. Using Visual Studio's debugger.

#### Linux

`valgrind` is a powerful set of memory debugging tools. It can help find leaks, use-after-frees, and more. It is useful for finding where memory-related bugs are occuring, with more information beyond the `Segmentation fault` message that is typically provided on crash. Sample usage:

```bash
valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --verbose ./a.out
```

Keep in mind your program may run **much** slower under memcheck depending on the flags you have set, and use much more memory.

| Flag | Usage | Notes |
| ---- | ----- | ----- |
| `--leak-check=full` | Detailed check for memory leaks |  |
| `--show-leak-kinds=all` | Report all types of memory leaks | definite, indirect, possible, reachable |
| `--track-origins=yes` | Find origins of uninitialized values | Can be very useful, but very slow |
| `--verbose` | More verbose output | Can repeat for more verbosity |
| `--log-file=your-log-file` | Write output to log file |  |

Ideally, you'll see something like this upon success:

```
HEAP SUMMARY:
    in use at exit: 0 bytes in 0 blocks
  total heap usage: n allocs, n frees, x bytes allocated
 
All heap blocks were freed -- no leaks are possible
 
ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)
ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)
```

## Attribute Specifier Sequence

Attributes are used to add extra information (metadata) to various language entities - functions, expressions, statements, and others, especially when no definitions of the function are available. They are commonly used to enhance warnings, enforce expected behavior, and provide additional information that can improve optimization. They have been common compiler extensions for a long time but weren't officially part of the language until C23, perhaps inspired by C++, where they were adopted with the C++11 standard. Several are defined by the language; they may be namespaced using the same syntax as found in C++ (for compatibility, clarity, and teaching purposes).

**Standard Attributes**<sub>(C23)</sub>

| Attribute | Signifies |
| --------- | --------- |
| `[[deprecated]]`<br>`[[deprecated]]("reason")` | this name/entity can be used, but is discouraged for `"reason"` |
| `[[fallthrough]]` | the fall-through from the previous `case x:` is intentional |
| `[[nodiscard]]`<br>`[[nodiscard]]("reason")` | the compiler should issue a warning if the return value is discarded |
| `[[maybe_unused]]` | the compiler should not warn about unused entities, if found |
| `[[noreturn]]` | the function does not return |
| `[[unsequenced]]` | the function is stateless, effectless, idempotent, and independent; less strict than `[[gcc::const]]` |
| `[[reproducible]]` | the function is effectless and idempotent; stricter than `[[gcc::pure]]` |

### Details on unsequenced and reproducible

**Effectless** - the function has no observable side effects (i.e., only modifies local variables and the contents of passed-in parameters).

**Idempotent** - the function produces the same result when called multiple times in a row

**Stateless** - the function's `static` or `thread_local` variables must be `const`, and cannot be `volatile`.

**Independent** - the function won't change global state, won't change any state via pointer parameters, and sees the same values for global variables.

## Assertions

`static_assert`, formerly `_Static_assert`<sub>(C11)</sub>; statically assert an expression to be true (!= 0) at compile time. Fail with an optional message otherwise. Useful for checking some problems before runtime; doesn't cause bloat or performance differences in the resulting executable.

```C
static_assert(2+2==4, "2+2 is not 4!");
```

## Build Systems

Note: these details also apply to C++ development.

Perhaps due to its age or complexity, there are a lot of build systems available for C/C++. For any reasonably-sized project, build system generators are a popular approach easing the build and installation process across multiple machines/platforms.

| Build System Generator | Supported Build Systems | Pros | Cons | Notes |
| ---------------------- | ---- | ---- | ----- | ---- |
| CMake | Make, Ninja, Visual Studio, Qt Creator | Widely used;<br>Domain-specific scripting language | Can be verbose;<br>Turnkey cross-platform development is tricky;<br>Version is important | Good for large projects;<br>Documentation is hit or miss. |
| Meson | Ninja, Visual Studio | Speed from Ninja backend;<br>Python-like syntax | Still growing in popularity ||

| Build System | Best for... | Overview | Notes |
| ------------ | ----------- | -------- | ----- |
| MSBuild | Windows environments | XML-based project files | Most useful on a Windows environment |
| Make | Small-medium projects | Target-oriented tasks | Can use on Windows;<br>Often cumbersome with large projects;<br>Can be used to automate other tasks besides building software |
| Ninja | Need fast, incremental builds | Recommended to use with build system generators | Originally developed by Google as a replacement for Make |

The basics of Make are covered in [C compilation](COMPILATION_C.md).

## External Libraries

## Using the Debugger

Tags: [[imperative language]] [[procedural language]] [[compiled language]] [[statically typed]] [[manifest types]] [[nominally typed]] [[pass-by-value]]
