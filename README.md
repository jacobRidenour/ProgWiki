# CodingPractice
This repository is meant to catalog my learning & experimentation with various (small) topics and documentation of them in various languages.

Setup instructions for my fallible memory and to ease things for others.

## Topics

| Syntax                                                                                                                                                                                                                                                                        | How to |     |
| ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- | ------ | --- |
| <ul><br>    <li>Definition of true/false</li><br>    <li>if/else, do/while, for</li><br>    <li>switch/case</li><br>    <li>break, continue, goto</li><br>    <li>Iterate over iterable type</li><br>    <li>Iterate over a range (inclusive vs. exclusive)</li><br></ul><br> |        |     |


## Recommended Applications
1. [Git](https://github.com/git-guides/install-git). Download code repositories, and version control your projects. Comes with git bash.
2. [Visual Studio Code](https://code.visualstudio.com/). Snappy code editor. Can be molded into somewhat of an IDE for a number of languages. Git integration and search capabilities are excellent. 
   - [Code - OSS](https://github.com/microsoft/vscode) if on Linux and your package manager's only option is a Flatpak.
3. [Visual Studio](https://visualstudio.microsoft.com/vs/) (Windows only). Top tier support for C++, C#, .NET. Integrated profiler. Built-in debugger works on *any* Windows executable. .NET UI designer tools.

## VS/Code Setup
Change Terminal to Bash:

| VSCode                                                             | VS2022 (Windows only)                                                             |
| ------------------------------------------------------------------ | --------------------------------------------------------------------------------- |
| Command Palette (Ctrl+Shift+P)<br>Terminal: Select Default Profile | Tools -> Options -> Environment -> Terminal -> Add;<br>Arguments: `--login -i -l` |
## C/C++ Essentials
See the [C README](C/README_C.md) for additional information on C, and the [C++ README](C++/README_C++.md) for additional information on C++.

### Windows

| Program                                                    | Add to PATH     | Rationale                                                                                                          |
| ---------------------------------------------------------- | --------------- | ------------------------------------------------------------------------------------------------------------------ |
| [Make](https://gnuwin32.sourceforge.net/packages/make.htm) | `/GnuWin32/bin` | Build automation tool. May be necessary to build dependencies.                                                     |
| [MinGW-w64](https://winlibs.com/)                          | `/mingw64/bin`  | Development environment for Windows apps, with ports of `gcc`, `gdb`, and more.                                    |
| [CMake](https://cmake.org/download/)                       | `/cmake/bin`    | Build system generator; creates build files (like Makefiles, Visual Studio projects) in a compiler-independent way |

Primer on Makefiles: \[[1](https://avikdas.com/2019/11/18/makefiles-from-the-ground-up.html)\] \[[2](https://avikdas.com/2019/12/16/makefiles-for-c-cpp-projects.html)\]

### Linux

| Program  | Rationale                                             |
| -------- | ----------------------------------------------------- |
| gcc      | GNU compiler collection; C/C++ compilers (gcc, g++)   |
| gdb      | GNU debugger (supports C/C++ among others)            |
| make     | See above                                             |
| binutils | Tools such as the linker, assembler, and binary tools |
| valgrind | Memory debugging, memory leak detection               |
| cmake    | See above                                             |

TODO: ninja? vcpkg?

## Python Setup

See Python/README_PYTHON.md for more information.

Download and install [Python](https://www.python.org/downloads/).

- During the installation, be sure to check "Add Python to PATH".
- Also be sure to add (PythonDirectory)/Scripts to PATH.
- Visual Studio natively supports Python projects.
- In VSCode, get the Python Extension Pack from the Marketplace, or minimally Python, Python Indent, and Python Environment Manager.

Make sure you can run python and pip from the command line and they're up to date. In a command prompt of your choice:

```
python --version
python -m pip --version
python -m pip install --upgrade pip setuptools wheel
```

// Ruby
// JSTS?
// Rust