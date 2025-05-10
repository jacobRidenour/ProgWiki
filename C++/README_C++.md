# C++

// templates (Boost.Hana and std library?)

// define programming paradigms in tags

The C++ programming language features ahead of time (AOT) compilation, and supports procedural (imperative) programming (like C), as well as functional, object-oriented, and generic programming. 

Its type system is static, partially inferred (vs. manifest in C), and nominal.

Function parameters are passed by value (copied), except for arrays, which are passed as pointers.

C++ has been standardized since 1998. Its development began in 1979 at Bell Labs by Bjarne Stroustroup as "C with classes", and was based on C in its early days. The content in this folder will reflect C++ from the first standard (C++98) up through the features included in the 2026 standard, C26.

> ⚠️ **Note**
> C++ is **not** a superset of C!

C++ aims to interoperate cleanly with C at the application binary interface (ABI) level, not just the source level. This means that:
* C++ can link to C functions and libraries
* Most C libraries can be used in C++ without modification
* Name mangling (more on that later) can be disabled by wrapping code in `extern "C" { ... }` to match C linkage expectations.

**Consequences of C compatibility:**
* Most of the C standard library is incorporated in the C++ standard
* Features that break C compatibility are typically avoided or carefully introduced
* There are joint standardization efforts to keep common language features, such as atomics, consistent between the two languages (i.e., there is some C++ influence on the more recent C standards)

**Incompatibilities with C:**
* Additional keywords reserved in C++: `new`, `class`, `template`, and many more
* Implicit conversion differences: `void*` doesn't implicitly convert to/from other pointer types
* Structs have enhanced capabilities in C++ (they can have constructors and methods just like a class)
* C99/C11 features are not fully supported in C++ (such as VLAs)

**Design Goals of C++:**
* Try not to invalidate C code unless absolutely required by a new feature
* Zero-cost abstractions whenever possible: write high-level code with no runtime penalty, just like C.

// Examples of C++ not being a superset of C?

## Creating a Binary

The steps of the compilation process are very similar to the C programming language, however, much of the parsing is context sensitive due to function and operator overloading, templates, name lookup (depending on scope, inheritance, and template instantiation context), as well as constructs that are ambiguous without semantic information. The complexity of the front-end for C++ compilation is much greater than that for C compilation.

In C++, symbols (such as functions) have their names **mangled** with information including type signatures, scopes, and namespaces. During compilation, a function `void foo(int, std::string)` will be transformed into something like `_Z3fooiNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEE` - this is C++'s way of making sure functions have unique names, unlike C, where everything shares the namespace, and you must be careful to name your functions in such a way that they are unlikely to conflict with others.

Unlike C, C++ may generate much code at compile time, most notably via templates (the mechanism for generic programming), which may require the compiler to track usage across translation unit boundaries, which can negatively impact compile time. Since templates can't be precompiled (outside of special support, e.g. in modules introduces in C++20), many third-party libraries available for C++ are header-only.

// Update organization as it relates to C++

## Objects

## Expressions

### Types

### Values

## Storage-Class Specifiers

## Type Qualifiers

## Operator Precedence & Associativity

## Memory Layout

## Memory Management

## VS Code Setup

### Windows

### Linux

## Build Systems

## External Libraries

## Using the Debugger