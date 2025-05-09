# Tools

Essential tools for various languages.

(TOC)

## Version Control

TODO: setup Git for Windows, generalized linux setup
// config/other files to tweak ?

## C/C++ Essentials
### Windows

| Program | Add to PATH | Rationale |
| ------- | ----------- | --------- |
| [Make](https://gnuwin32.sourceforge.net/packages/make.htm) | `/GnuWin32/bin` | Build automation tool. May be necessary to build dependencies.                                                     |
| [MinGW-w64](https://winlibs.com/)                          | `/mingw64/bin`  | Development environment for Windows apps, with ports of `gcc`, `gdb`, the GNU C standard library, and more.                                    |
| [CMake](https://cmake.org/download/)                       | `/cmake/bin`    | Build system generator; creates build files (like Makefiles, Visual Studio projects) in a compiler-independent way |

Note that Visual Studio comes with the C standard library/headers; you gain access to the legacy Microsoft Visual C++ C Runtime (MSVCRT). The C99-compliant Universal C Runtime (UCRT) ships with the OS since Windows 10. The Visual Studio installer
(Microsoft C Runtime Library (CRT)). The installer can also nab you the Windows SDK, providing Windows API access.

### Linux

| Program   | Rationale                                             |
| --------- | ----------------------------------------------------- |
| gcc       | GNU compiler collection; C/C++ compilers (gcc, g++)   |
| gdb       | GNU debugger (supports C/C++ among others)            |
| make      | See above                                             |
| binutils  | Tools such as the linker, assembler, and binary tools |
| libc6-dev | C standard library / headers                          |
| valgrind  | Memory debugging, memory leak detection               |
| cmake     | See above                                             |

For C/C++ this repository focuses on the Make, CMake, and MSBuild build systems.

The `build-essential` package on Linux typically includes `gcc`, `g++`, `make`, and a C library (typically `libc`)

## Haskell Essentials
### Windows

TODO

### Linux

| Program       | Rationale               |
| ------------- | ----------------------- |
| ghc           | FOSS Haskell Compiler   |
| cabal-install | Haskell package manager |

