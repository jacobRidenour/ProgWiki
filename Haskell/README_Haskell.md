# Haskell

The Haskell programming language supports functional (declarative) programming. Its type system is static, inferred, and nominal. 

Function parameters are passed by value (copied), but values are typically not computed until needed due to using a lazy evaluation model.

Haskell was first standardized in 1990. The [Haskell Report](https://wiki.haskell.org/Language_and_library_specification), its free specification, was last updated in 2010.

Like C, multiple implementations exist. This project focuses on the Glasgow Haskell Compiler (`ghc`), which provides both ahead of time (AOT) compilation and an interpreter (`ghci`).

## Creating a Binary

References: [[1]](https://aosabook.org/en/v2/ghc.html)

There are 3 main components of `ghc`:
* the runtime system (RTS),
* the boot libraries, and
* the compiler itself

### The Runtime System (RTS)

The RTS is a large C-based library that is necessary to run compiled Haskell programs.

### Boot Libraries

The boot libraries implement low-level details of the Haskell language, and are often tightly coupled to `ghc`.

### Compilation & Assembly

The compiler turns Haskell code into machine code.



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

Tags: [[functional language]] [[declarative language]] [[compiled language]] [[interpreted language]] [[statically typed]] [[inferred types]] [[nominally typed]] [[pass-by-value]]