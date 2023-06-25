# C++ Setup
Visual Studio uses its own compiler ```cl.exe```. I Recommend VS/CMake for any larger projects in C/C++ due to the fine-grained control for different Platforms/Configurations.
For convenience I recommend adding ```C:\Program Files\Microsoft Visual Studio\2022\Community\VC\Tools\MSVC\14.34.31933\bin\Hostx64\x64``` to your PATH.

## Build with your IDE

**VSCode**
* Get C/C++ Extension Pack
* Settings (Ctrl+,) -> Extensions -> C/C++ -> c_cpp_runner
    * Cpp Standard: c++20
    * C Standard: c17

**VS2022**
Some useful default settings for your projects. Some of these may already be set by default.
* Project -> Properties -> Configuration: All Configurations
    * Configuration Properties -> General:
        * Output Directory: ```$(SolutionDir)$(ProjectName)\build\$(Platform)\$(Configuration)\```
        * Intermediate Directory: ```$(SolutionDir)$(ProjectName)\build\ints\$(Platform)\$(Configuration)\```
        * C++ Language Standard: ISO C++ 20 Standard
        * C Language Standard: ISO C17 (2018) Standard
    * Configuration Properties -> Advanced
        * Character Set: Use Unicode Character Set
    * Configuration Properties -> C/C++
        * -> General -> SDL checks: Yes (/sdl)
        * -> Language -> C++ Language Standard: ISO C++ 20 Standard
        * -> Language -> C Language Standard: ISO C17 (2018) Standard
        * -> Language -> Conformance mode: Yes (/permissive)
    * Linker -> System -> Subsystem
        * ```Console (/SUBSYSTEM:CONSOLE)```
        * Without this setting, your output console will close automatically once the program has finished.
* Project -> Properties -> Configuration: Debug
    * Configuration Properties -> Advanced:
        * Use Debug Libaries: Yes
    * Configuration Properties -> C/C++
        * -> General -> Warning Level: EnableAllWarnings (/Wall)
        * -> Preprocessor -> Preprocessor Definitions -> <Edit...>
            * Add: _DEBUG
* Project -> Properties -> Configuration: Release 
    * Configuration Properties -> Advanced:
        * Use Debug Libaries: No
    * Configuration Properties -> C/C++
        * -> General -> Warning Level: Level3 (/W3)
        * -> Optimization -> Enable Intrinsic Functions: Yes (/Oi)
        * -> Preprocessor -> Preprocessor Definitions -> <Edit...>
            * Add: NDEBUG
        * -> Code Generation -> Enable Function-Level Linking: Yes (/Gy)
        * -> Code Generation -> Enable Enhanced Instruction Set: Streaming SIMD EXtensions (/arch:SSE)
    * Configuration Properties -> Linker
        * -> General -> Treat Linker Warnings As Errors: Yes (/WX)
        * -> Optimization -> References: Yes (/OPT:REF)
        * -> Optimization -> Enable COMDAT Folding: Yes (/OPT:ICF)

### Including Additional Files and Linking Libraries
If you just want to include additional files from within the same directory as the .cpp file with your main() function, simply ```#include "localfile.hpp"```. This section focuses on external libraries and setting things up with the project in ```/BoostDemo/```.

Boost has a lot of useful libraries, and plenty of them are header only (i.e. you don't need to compile them). Word of warning, setting this up is a little bit less streamlined if you're using VSCode.
1. Get [Boost](https://www.boost.org/) and extract it.
2. Copy /boost_1_82_0/ to a directory of your choice (I did C:\.include). We are going to build it to practice not only adding include directories but also statically linked libraries (.lib or .a files).
Open Git Bash:
```cd /c/.include/boost_1_82_0/```

If you will be building with Visual Studio:
```
./bootstrap
./b2
```
If you will be building with g++/Visual Studio Code (Assumption: you have Mingw-w64):
```
./bootstrap mingw
./b2 toolset=gcc
```
Note that you can use the MSVC compiler in Visual Studio Code, but we're not going to for the sake of learning.

(Optional) Copy (cp) or Move (mv) the library files (.lib for MSVC, .a for mingw) into a single directory for convenience. FYI you can paste into a Bash terminal using Mouse3.
```
mkdir lib
cd /c/.include/boost_1_82_0/bin.v2/libs
find ./ -name '*.lib' -exec cp -prv '{}' '/c/.include/boost_1_82_0/lib' ';'
```

**VSCode**
* Settings (Ctrl+,) -> Extensions -> 
    * C/C++ -> Intellisense & C/C++ Runner
        * Add C:\.include\boost_1_82_0 as an item under Include Path
* Edit tasks.json, under the args section, add these lines:
    * FYI: feel free to steal my tasks.json to use as a template for your own projects. It has two separate build types so you can comfortably build debug and release versions. Proper library linking is important - debug builds have much worse performance than release builds but retain tons of information that's helpful for solving problems. Tasks.json is normally located in your workspace's ```.vscode``` folder
    * ```"-IC:\\.include\\boost_1_82_0"``` - so the compiler knows what folder to search
    * ```"-LC:\\.include\\boost_1_82_0\\lib"``` - so the compiler knows where library (.a, .lib, .dll) files are located. If you skipped the last part in step 2 above, you will need to specify the folder where libboost_filesystem-...-.lib is located.
    * For debug build:
        * ```"-lboost_filesystem-mgw13-mt-d-x64-1_82"```
    * For release build:
        * ```""-lboost_filesystem-mgw13-mt-x64-1_82""```
You can try to compile now, but you will still run into errors - it's a bit more cryptic to figure out with VSCode than Visual Studio, but the error is because the Boost Filesystem library also depends on the Boost Chrono library (partly why I used that library directly in this sample program!), so we need to add that as well:
    * ```"-lboost_chrono-mgw13-mt-d-x64-1_82"``` (Debug)
    * ```"-lboost_chrono-mgw13-mt-x64-1_82"``` (Release)
Notice that in both cases we omitted the "lib" that prefixes the beginning of the .lib/.a files

**VS2022**
1. We don't have an existing project, so on launch click "Continue without code".
2. File > New > Project from existing code. Keep project type as Visual C++.
3. Project file location: directory containing boost-demo.cpp. Project name: BoostDemo.
4. How do you want to build the project? For now choose Use Visual Studio and change Project type to Console application project.
    * If you know what you're doing you can add Include search paths now, otherwise don't worry about it. Then click Finish.
5. Go to Project -> BoostDemo properties. Under Configuration (top left) select All Configurations.
6. Configuration Properties -> C/C++ -> General -> Additional Include Directories -> Edit...
    * Add: ```C:\.include\boost_1_82_0```
    * Note: you can instead add this under VC++ Include Directories; be warned this changes settings for *all* C/C++ projects in Visual Studio and not just the current one.
7. Configuration Properties -> Linker -> General -> Additional Library Directories -> Edit...
    * Add: ```C:\.include\boost_1_82_0\lib```

## Building with CMake
Check out CMake-Notes.md to learn more about the basic anatomy and functionalities available in CMake.
Sample CMakeLists.txt to do the same build:
```
cmake_minimum_required(VERSION 3.0)
project(boost-demo LANGUAGES CXX)

# Set the source file and output directory
set(SOURCE_FILE boost-demo.cpp)
set(OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/bin)

# Set the Boost library directories and names
set(BOOST_INCLUDE_DIR C:/.include/boost_1_82_0)
set(BOOST_LIB_DIR C:/.include/boost_1_82_0/lib)
set(BOOST_LIBS_DEBUG boost_filesystem-mgw13-mt-d-x64-1_82 boost_chrono-mgw13-mt-d-x64-1_82)
set(BOOST_LIBS_RELEASE boost_filesystem-mgw13-mt-x64-1_82 boost_chrono-mgw13-mt-x64-1_82)

# Debug build target
add_executable(${PROJECT_NAME}-debug ${SOURCE_FILE})
target_compile_options(${PROJECT_NAME}-debug PRIVATE -g -fdiagnostics-color=always)
target_include_directories(${PROJECT_NAME}-debug PRIVATE ${BOOST_INCLUDE_DIR})
target_link_directories(${PROJECT_NAME}-debug PRIVATE ${BOOST_LIB_DIR})
target_link_libraries(${PROJECT_NAME}-debug PRIVATE ${BOOST_LIBS_DEBUG})
set_target_properties(${PROJECT_NAME}-debug PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${OUTPUT_DIRECTORY}
)

# Release build target
add_executable(${PROJECT_NAME}-release ${SOURCE_FILE})
target_compile_options(${PROJECT_NAME}-release PRIVATE -O3)
target_include_directories(${PROJECT_NAME}-release PRIVATE ${BOOST_INCLUDE_DIR})
target_link_directories(${PROJECT_NAME}-release PRIVATE ${BOOST_LIB_DIR})
target_link_libraries(${PROJECT_NAME}-release PRIVATE ${BOOST_LIBS_RELEASE})
set_target_properties(${PROJECT_NAME}-release PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${OUTPUT_DIRECTORY}
)
```
Since the output directory is set to /bin/ make the directory and navigate to it in your terminal, then:
```
cmake ..
```
If you're building in Visual Studio:
```
make
```
This will create a Visual Studio project for you with the specified settings in CMakeLists.txt

If you're building from the command line/Visual Studio Code:
```
cmake .. -G "MinGW Makefiles"
```
This will create a MinGW Makefile for you with the specified settings in CMakeLists.txt

## Building with Makefiles
Sample Makefile to do the same build:
```
CXX = g++
CXXFLAGS_DEBUG = -g -fdiagnostics-color=always
CXXFLAGS_RELEASE = -O3

INCLUDE_DIR = C:/.include/boost_1_82_0
LIB_DIR = C:/.include/boost_1_82_0/lib

BOOST_LIBS_DEBUG = -lboost_filesystem-mgw13-mt-d-x64-1_82 -lboost_chrono-mgw13-mt-d-x64-1_82
BOOST_LIBS_RELEASE = -lboost_filesystem-mgw13-mt-x64-1_82 -lboost_chrono-mgw13-mt-x64-1_82

debug: boost-demo.cpp
	$(CXX) $(CXXFLAGS_DEBUG) -o C:/.../C++/BoostDemo/boost-demo-debug.exe $< -I$(INCLUDE_DIR) -L$(LIB_DIR) $(BOOST_LIBS_DEBUG)

release: boost-demo.cpp
	$(CXX) $(CXXFLAGS_RELEASE) -o C:/.../BoostDemo/boost-demo-release.exe $< -I$(INCLUDE_DIR) -L$(LIB_DIR) $(BOOST_LIBS_RELEASE)
```
Breaking down the anatomy; Makefiles are powerful but can become messy with complicated projects.

CXX refers to the compiler, the flags are specific flags you want to use for specific builds. The other variables (for libraries to link) are for convenience, and so if you need to add more libraries, you only need to edit a single line. Just running "make" will run the first target (debug). The Makefile included in ```/BoostDemo/``` has a more generic implementation that can be usaed with other similarly structured projects.

Creating Makefiles manually can quickly become messy, I recommend learning the basics of CMake to streamline the process and save you from some headaches.