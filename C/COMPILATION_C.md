# Compilation

Basics of C program compilation using bare gcc and simple Makefiles.

## Single file program

See the [Options Summary for gcc](https://gcc.gnu.org/onlinedocs/gcc/Option-Summary.html) for more information.

```bash
gcc filename.c -g -Wall -Werror -Wcast-align=strict -Wpedantic -lm -o MyProg
```

| Flag | Category | Effect | 
| ---- | -------- | ------ | 
| `-g` | Debugging | include debugging information in the output |
| `-Wall` | Warnings | enable warnings for (often) suspicious/easy to avoid constructions |
| `-Werror` | Warnings | treat warnings as errors |
| `-Wcast-align=strict` | Warnings | enable warnings for pointer casts that increase the target's alignment (e.g. `int* <- char*`) |
| `-Wpedantic` | Warnings | enable warnings for usage of language extensions (not part of the ISO C/C++ standard) |
| `-lm`| Linker | `l`ink to library `m`; math library in this case.<br>Typical syntax to link to a specific library |
| `-o MyProg` | Output | Output should be a file called MyProg;<br>filename is `a.out` if not provided. |

## Multi-file program

```bash
# Create object files
gcc -c filename1.c -o filename1.o -I./include # -g -...
gcc -c filename2.c -o filename2.o -I./include # -g -...
# Link the object files together
gcc filename1.o filename2.o -o MyProg -L./lib -lm
```

| Flag | Category | Effect | 
| ---- | -------- | ------ | 
| `-c` | Compilation | compile translation unit (\*.c file) into object file (\*.o) |
| `-I ./include` | Include | include `./include` in the list of directories to search for header (\*.h) files;<br>may be repeated as necessary |
| `-L./lib` | Linker | include `./lib` in the list of directories to search for library files;<br>may be repeated as necessary |

For multi-file programs, it is best practice to create object files for each source file; this way, no time is wasted recompiling code that has not changed. This becomes more important with larger projects.

You could write a shell script to do the compilation for you, that is perfectly valid. However, as your project grows, so does the complexity of handling dependencies between files and tasks, executing commands with those dependencies in mind, and the performance lost from lack of built-in support for incremental builds and parallel builds.

## Make basics

Often - or maybe even canonically - C projects tend to be built using Make. As is too often the case, Make was originally developed at Bell Labs in the 1970s, and became ubiquitous in part for being better than what came before (cumbersome shell scripts), and also for being included in Unix from the early days. There have been a number of Make implementations; in the wild, you're most likely to come across GNU Make or Microsoft's nmake. Different implementations are not necessarily compatible; this document focuses on GNU Make.

At a high level, Make can be used to automate repetitive tasks in a generic, dependency-driven way. Its basic unit is a rule, defined as a target, its dependencies, and the rules to satisfy the targets. All of these rules are usually<sup>†</sup> contained in a Makefile. Make checks the timestamps of dependencies to decide whether the rule needs to be re-run, i.e. reducing unnecessary recompilations. The language of Make is text-based and not token-based, i.e. variables are strings. Variables are sometimes referred to as macros in Make parlance.

The basic syntax is fairly ~~Pythonic~~ similar to your typical Unix shell. No quotes necessary around variables with spaces. There are two assignment operators, `=` and `:=`, which have different meanings. You can add to variable with the compound assignment operator `+=`, and define them if not yet defined with `?=`.

| Assignment Operator | Effect | 
| ------------------- | ------ |
| `=` (recursive/lazy) | variable expanded and evaluated at each reference |
| `:=` or `::=` (simple/immediate) | variable evaluated immediately and persists |

```make
# Variable names are case-sensitive and must not contain :#= or whitespace
CC = gcc
# Note CC stands for C Compiler
CFLAGS = -c -Wall
DBGFLAGS := -g

target: dependencies
    recipe
```

<sup>†</sup><sub>Make will guess how to compile a single source file, e.g. HelloWorld.c; `make HelloWorld` will try to compile the program with `cc HelloWorld.c -o HelloWorld`. You could put necessary variables like include paths and libraries to link to in the Makefile, and provide no rules; these variables will be used when Make guesses what to do.</sub>

| Component | Definition |
| --------- | ---------- |
| `target` | usually: name of output file or action to perform |
| `dependencies` | files or other targets that need to be present (and updated if needed) before `command` can be run. |
| `recipe` | command(s) to satisfy the `target`. Line **must start with a tab**<sup>†</sup> `:(`;<br>runs commands with `/bin/sh`; override by setting the variable `SHELL` |

<sup>†</sup><sub>If you are using GNU Make version 3.82 or newer (check with `make -v`), there is a special variable that can change the prefix from tab to another character. For example, to change to `>`, add `.RECIPEPREFIX = >` before your rules.</sub>

### Variables & Wildcards
---

To avoid repeating yourself for every *.c file etc., we can make use of the wildcard `%` and Make's automatic variables in rules:

```make
%.o: %.c
    gcc -c -Wall -o $@ $<
```

You can repeat yourself even less<sup>†</sup> and make your Makefile harder to read for the uninitialized with variables:

```make
%.o: %.c
    $(CC) $(CFLAGS) -o $@ $<
```

<sup>†</sup><sub>The Don't Repeat Yourself (DRY) principle is usually worth applying to things that are likely to change as your project evolves. On the other hand, [premature optimization](https://xkcd.com/1691/) is the root of all evil.</sub>

User-defined variables are substituted with $(parentheses). Automatic variables are not. As always in this repository, more detailed information can be found in the associated [documentation](https://www.gnu.org/software/make/manual/html_node/index.html).

| Automatic variable | Meaning | 
| ------------------ | ------- |
| `$@` | name of the target of this recipe |
| `$<` | name of the first dependency |
| `$^` | names of all dependencies, whitespace-delimited |
| `$*` | the string matching the `%` wildcard (stem) |

#### The `wildcard` function
---

Wildcards such as `%` are not expanded when variables are set, or within function arguments. If you need wildcards in such cases, you can use the `wildcard` function, e.g. to get all of the `*.c` files in the current directory:

```make
$(wildcard *.c)
```

#### Pattern substitution
---

You are likely to come across or use the **pat**tern **subst**itution function [`patsubst`](https://www.gnu.org/software/make/manual/html_node/Text-Functions.html); as seen on that page, a common usage is to replace a file's extension with another. The substitution reference pattern `$(var:pattern=replacement)` is shorthand for this; you may find it easier to read.

```make
# Notice no spaces between the parameters
$(patsubst pattern,replacement,$(var))
# is equivalent to:
$(var:pattern=replacement)

# e.g.
SRCS = $(wildcard *.c)
OBJS = $(SRCS:.c=.o)
```

### Recursion

Since the commands specified by your `recipe` are run in the shell, you can [use Make recursively](https://www.gnu.org/software/make/manual/make.html#Recursion). This separation is a perfectly valid idea, but recursion is not the recommended approach for splitting a single project; it is more appropriate for projects that depend on other independent projects. See [this paper from 1998](https://web.archive.org/http://aegis.sourceforge.net/auug97.pdf) for more details. The author summarizes the root of the problem with:

> "Incomplete `Makefiles` are *wrong* `Makefiles`."

The long and short version is that Make builds a directed acyclic graph (DAG) of all dependencies, and with recursive Make, parts of the graph are isolated from each other, which leads to unintuitive behavior and (often) unnecessary rebuilds.

We want to use logical separation in our Makefile and retain arbitrary directory structure, avoiding absolute paths at all costs.

// The recommended approach instead is to use the `include` directive in your Makefile.

```make
TODO: test includes

.INCLUDE : file1 file2 ...
.INCLUDE : 

```

// When make encounters a rule like this in a makefile, it reads in the contents of the given files (in order from left to right) and uses their contents as if they had appeared in the current makefile. For example, suppose the file macrodef contains a set of macro definitions. Then: 

```make
.INCLUDE : file1 file2 ...
.INCLUDE : macrodef
```

// obtains those macro definitions and processes them as if they actually appeared at this point in the makefile. It is possible to store includable files under other directories. To do this, you use another special target: 

```make
.INCLUDEDIRS: dir 2 dir2 ...


```

### Implicit Rules

As alluded to above, you can run Make when no Makefile exists and still get a successful compilation to occur, despite not providing any rules. You can avoid defining some rules, such as the creation of `.o` files, this way.

`-r` or `--no-builtin-rules` disables all predefined rules. Examples of some implicit rules you may want to take advantage of:

```make
# C compilation
n.o: n.c
    $(CC) $(CPPFLAGS) $(CFLAGS) -c

# C++ compilation
n.o: n.cc | n.cpp | n.C
    $(CXX) $(CPPFLAGS) $(CXXFLAGS) -c

# Linking 1 .o file
n: n.o
    $(CC) $(LDFLAGS) n.o $(LDLIBS)
```

| Implicit Variable | Usage |
| ----------------- | ----- |
| `CC` | C compiler executable |
| `CXX` | C++ compiler executable |
| `CFLAGS` | compiler flags for `CC` |
| `CXXFLAGS` | compiler flags for `CXX` |
| `CPPFLAGS` | compiler flags for the C preprocessor (and C/C++ compiler) |
| `LDFLAGS` | linker flags for `ld` |
| `LDLIBS` | library flags/names for `ld` |

These variables are often redefined for clarity.

### Phony Targets
---

You can define targets that don't actually correspond to any files by defining them as "phony". These targets shouldn't share their name with files in your project, or Make will consider them targets.

```make
# .PHONY: target1 target2 ... targetN
.PHONY: clean

clean:
    rm -f *.o programName
```

### Dependency Management


### Conditional Compilation






...

Another quirk, your targets and prerequisites may not contain whitespace. Use relative paths wherever possible. You can have `make` detect and throw an error if the current directory contains a whitespace:

```make
ifneq (1,$(words $(CURDIR)))
$(error Containing path cannot contain whitespace: '$(CURDIR)')
endif
```

It's *probably easier* to use a build system generator for any complex or long-lived projects relative to writing your own portable Makefiles.

// TODO
// parallel execution -j#  (blank for all cores)
// note first rule is default if none specified; can explicitly set one with .DEFAULT_GOAL

// include $(OBJ_DIR)/src_rules.mk
// include $(OBJ_DIR)/lib_rules.mk
// -> offer logical separation
// TODO: separate debug/release builds
// TODO: make install

### Template Makefile

Skeleton for small projects

```Make
ifneq (1,$(words $(CURDIR)))
$(error Containing path cannot contain whitespace: '$(CURDIR)')
endif

SHELL := bash
.RECIPEPREFIX = >
.PHONY: clean help
default: help

SRCS = $(wildcard *.c)
OBJS = $(SRCS:.c=.o)
OUT := a.out

CC := gcc
CFLAGS := -Wall -Werror -Wcast-align=strict -Wpedantic
# INCLUDES := -I../__tests/

# LDFLAGS := library/dirs
LDLIBS := -lm

release: $(OBJS) # Create a Release (optimized) build
> $(CC) $(SRCS) $(CFLAGS) $(INCLUDES) $(LDLIBS) -o $(OUT)

help: # Show help for each of the Makefile recipes.
> @grep -E '^[a-zA-Z0-9 -]+:.*#'  Makefile | sort | while read -r l; do printf "\033[1;32m$$(echo $$l | cut -f 1 -d':')\033[00m:$$(echo $$l | cut -f 2- -d'#')\n"; done

```

`help` target from dwmkerr's [makefile-help](https://github.com/dwmkerr/makefile-help).

Tags: 