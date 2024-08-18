# CodingPractice
This repository is meant as a catalog/reference for various aspects of different programming languages, syntax, type systems, compilation, build systems, and performing common tasks (setting up/using relevant libraries when applicable).

Written from the perspective of a new college graduate. Trying to lean more towards practical over theoretical.

Jump to any language's README:  
[--> C](C/README_C.md)

## Topics

<table>
  <tr>
    <td valign="top">
      <strong>Operators</strong>
      <ul>
        <li>Numerical operators (+ - * / % sqrt **)</li>
        <li>Increment/decrement (++ --)</li>
        <li>Bitwise operators (& | ~ !)</li>
        <li>Compound operators</li>
        <li>Logical operators (&gt; &lt; ==)</li>
        <li>Operator associativity & precedence</li>
      </ul>
    </td>
    <td valign="top">
      <strong>Type system</strong>
      <ul>
        <li>Numeric types</li>
        <li>Aggregate types</li>
        <li>Type qualifiers</li>
        <li>Storage-class specifiers</li>
        <li>Pointers, references</li>
        <li>Type conversion & casting</li>
        <li>Copying/cloning</li>
      </ul>
    </td>
  </tr>
  <tr>
    <td valign="top">
      <strong>Conditionals</strong>
      <ul>
        <li>Definition of true/false</li>
        <li>Selection statements</li>
        <li>Iteration statements</li>
        <li>Jump statements</li>
      </ul>
    </td>
    <td valign="top">
      <strong>Data Structures</strong>
      <ul>
        <li>Iterate over iterable type</li>
        <li>Dictionaries/Maps, Sets, Tuples</li>
        <li>Arrays/vectors, linked lists</li>
        <li>Multidimensional arrays</li>
        <li>Hash tables, hash maps</li>
        <li>Stacks, queues, deques</li>
        <li>Graphs, Trees</li>
      </ul>
    </td>
  </tr>
</table>

<table>
  <tr>
    <td valign="top">
      <strong>Strings/Files</strong>
      <ul>
         <li>Strings (print/format, concat, case, sort, split)</li>
         <li>Write to/read from the console, file, binary file</li>
         <li>Traverse the file system</li>
         <li>Parse JSON, XML, CSV</li>
         <li>Regular expressions</li>
         <li>Built-in/common logging techniques</li>
         <li>Date & time recording, manipulation, formatting</li>
      </ul>
    </td>
    <td valign="top">
      <strong>Functions, Objects, Memory</strong>
      <ul>
         <li>Passing & returning semantics</li>
         <li>Error handling (try-catch, return values)</li>
         <li>Abstract classes</li>
         <li>Inheritance and polymorphism</li>
         <li>Access specifiers and visibility</li>
         <li>Keywords otherwise not covered</li>
         <li>Operator overloading</li>
      </ul>
    </td>
  </tr>
  <tr>
    <td valign="top">
      <strong>Multithreading</strong>
      <ul>
         <li>Threading/multiprocessing syntax</li>
         <li>Conditions, mutexes, synchronization</li>
      </ul>
    </td>
    <td valign="top">
      <strong>Networking</strong>
      <ul>
         <li>Send HTTP requests, handle responses</li>
         <li>Basic Socket programming</li>
      </ul>
    </td>
  </tr>
</table>

<strong>Language External</strong>
<ul>
   <li>Language description</li>
   <li>Creating a Binary</li>
   <li>Build systems</li>
   <li>External Libraries</li>
   <li>Using the Debugger</li>
   <li>Virtual environments</li>
</ul>


## Recommended Applications
1. [Git](https://github.com/git-guides/install-git). Download code repositories, and version control your projects. Comes with git bash (Windows).
2. [Visual Studio Code](https://code.visualstudio.com/). Snappy code editor. Can be molded into somewhat of an IDE for a number of languages. Git integration and search capabilities are excellent. 
   - [Code - OSS](https://github.com/microsoft/vscode) if on Linux and your package manager's only option is a Flatpak.
3. [Visual Studio](https://visualstudio.microsoft.com/vs/) (Windows only). Top tier support for C++, C#, .NET. Integrated profiler. Built-in debugger works on *any* Windows executable<sup>†</sup>; .NET UI designer tools.

<sup>† Seriously!</sup>

## VS/Code Setup

Language-specific setup for VS/Code in [VSCODE.md](VSCODE.md).

## C/C++ Essentials
### Windows

| Program | Add to PATH | Rationale |
| ------- | ----------- | --------- |
| [Make](https://gnuwin32.sourceforge.net/packages/make.htm) | `/GnuWin32/bin` | Build automation tool. May be necessary to build dependencies.                                                     |
| [MinGW-w64](https://winlibs.com/)                          | `/mingw64/bin`  | Development environment for Windows apps, with ports of `gcc`, `gdb`, and more.                                    |
| [CMake](https://cmake.org/download/)                       | `/cmake/bin`    | Build system generator; creates build files (like Makefiles, Visual Studio projects) in a compiler-independent way |

### Linux

| Program  | Rationale                                             |
| -------- | ----------------------------------------------------- |
| gcc      | GNU compiler collection; C/C++ compilers (gcc, g++)   |
| gdb      | GNU debugger (supports C/C++ among others)            |
| make     | See above                                             |
| binutils | Tools such as the linker, assembler, and binary tools |
| valgrind | Memory debugging, memory leak detection               |
| cmake    | See above                                             |

For C/C++ this repository focuses on the Make, CMake, and MSBuild build systems.

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

// C++
// Python
// Ruby
// JS/TS
// Rust

// git clear ignored files: git rm -r --cached . && git add . && git commit -am "Remove ignored files"