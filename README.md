# CodingPractice
Learning basics of C/C++, Python, Rust.
Goal: this code and documentation helps others wanting to learn.

## Things to Get and Why
1. Get [Visual Studio](https://visualstudio.microsoft.com/vs/) and [Visual Studio Code](https://code.visualstudio.com/). VS is especially good for C/C++ projects, VSCode is good for many other languages.
2. Get [Git](https://github.com/git-guides/install-git); quickly get various open-source projects on GitHub, version control on your own projects. VSCode and VS2022 both have great support for Git.
3. Get [Make](https://gnuwin32.sourceforge.net/packages/make.htm) and add ```/GnuWin32/bin``` to your PATH. It's one option to build C/C++ projects; not strictly necessary but nice to have if you want to learn the basics of Makefiles.
4. Get [MinGW-w64](https://winlibs.com/) and add ```/mingw64/bin``` to your PATH. It's another option to build C/C++ projects (our own or others); probably the preferred option if we're not using Visual Studio.
5. Get [CMake](https://cmake.org/download/) and add ```/cmake/bin``` to your PATH if it's not there after installation. It's a great way to keep build files separate from source files and make building C/C++ projects less painful, especially if we're outside the Visual Studio environment. For more details on how to set it up, see ```/C++/BoostDemo/Cmake-Notes.md```.

## VS/Code Setup
**VSCode**
* Change terminal to Git Bash (Ctrl+Shift+P) Terminal: Select Default Profile
* Build shortcut: Ctrl+Shift+B

**VS2022**
* Tools -> Options -> Environment -> Terminal -> Add; for Bash, set arguments ```--login -i -l```

## C/C++ Setup

See C++/README_C++.md

## Python Setup


## Rust Setup
Download/run rustup from rust-lang.org
VSCode: Get Rust Extension Pack
Create your project:
```
cd Rust/project
cargo new <project-name>
code .
```

Build/run your project:
```
cargo build
cargo run
```

