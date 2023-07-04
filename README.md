# CodingPractice
Learning basics of different languages. So far:
* C++
* Python

Planned:
* Rust

I hope that the code and documentation here helps others wanting to learn.

## Things to Install

1. Get [Git](https://github.com/git-guides/install-git). It's great to quickly get various open-source projects on GitHub, and do proper version control on your own projects. VSCode has great support for Git, and Visual Studio's is getting better.
2. Get [Visual Studio Code](https://code.visualstudio.com/). Great code editor and can be finagled into being an IDE for a number of languages.
3. Get [Visual Studio](https://visualstudio.microsoft.com/vs/). VS is especially good for C/C++ projects, also supports several other popular languages such as Python, Visual Basic, C#, and F#.

## VS/Code Setup
**VSCode**
* Change terminal to Git Bash (Ctrl+Shift+P) Terminal: Select Default Profile
* Build shortcut: Ctrl+Shift+B

**VS2022**
* Tools -> Options -> Environment -> Terminal -> Add; for Bash, set arguments ```--login -i -l```

## C/C++ Setup

See C++/README_C++.md for more information.

1. Get [Make](https://gnuwin32.sourceforge.net/packages/make.htm) and add ```/GnuWin32/bin``` to your PATH. It's a build automation tool for C/C++ projects from makefiles; not strictly necessary but nice to have if you want to learn the basics of Makefiles.
2. Get [MinGW-w64](https://winlibs.com/) and add ```/mingw64/bin``` to your PATH. It's an environment to build C/C++ projects (our own or others); probably the preferred option if we're not using Visual Studio. Comes with a port of GCC, GNU Binutils, and some tools for using the Windows API.
3. Get [CMake](https://cmake.org/download/) and add ```/cmake/bin``` to your PATH if it's not there after installation. It's a great cross-platform, open-source build automation tool, getting things ready to be built by the compiler of your choice. It can make building large C/C++ projects less painful, especially if we're outside the Visual Studio environment. For more details on how to set it up, see ```/C++/BoostDemo/Cmake-Notes.md```.

## Python Setup

See Python/README_PYTHON.md for more information.

Download and install [Python](https://www.python.org/downloads/).
* During the installation, be sure to check "Add Python to PATH".
* Also be sure to add (PythonDirectory)/Scripts to PATH.
* Visual Studio natively supports Python projects.
* In VSCode, get the Python Extension Pack from the Marketplace, or minimally Python, Python Indent, and Python Environment Manager.

Make sure you can run python and pip from the command line and they're up to date. In a command prompt of your choice:
```
python --version
python -m pip --version
python -m pip install --upgrade pip setuptools wheel
```

## Rust Setup
Download and install [rustup-init](https://www.rust-lang.org/tools/install)
* In VSCode, get the Rust Extension Pack from the Marketplace.

In a command prompt of your choice...
1. Create your project:
```
cd Rust/project
cargo new <project-name>
code .
```

2. Build/run your project:
```
cargo build
cargo run
```

