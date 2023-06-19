# CMake Notes
Going over the basics for first-time users and learning how it works myself. Try yourself getting boost-demo.cpp built on your machine using CMake.

Read/reference the [CMake documentation](https://cmake.org/cmake/help/latest/)

## Create a CMakeLists.txt in the root of your project
Example CMakeLists.txt:
```
cmake_minimum_required(VERSION 3.2)
project(boostdemo LANGUAGES CXX)
add_executable(${PROJECT_NAME} boost-demo.cpp)
```
* Should be placed in the root folder of your project.
* ```"LANGUAGES ..."``` is not strictly necessary, but helpful so CMake looks for the right compiler.
* ```boost-demo.cpp``` listed under add_executable because it's in the same directory as CMakeLists and it has our main() function.

## Make a build directory
```mkdir /project-root/build```
Try to run ```Cmake``` while in /build/, and you will see that it generates several files in that build folder. If you're trying to build something like hello-world.cpp you can run ```cmake .. \ make``` and it will build such a project for you.

## Once you've run CMake once...
i.e. you have a CMake Cache folder.
You can run ```cmake``` or ```ccmake``` or ```cmake_gui``` on the build directory and won't need to provide the source again.
ccmake and cmake_gui are both gui-based CMake options that let you set project configuration.

## Create variables
Syntax: ```set(VARNAME "var contents")```

## Functions and Macros
What's the difference? Why should you use them?

1. Taking a built-in function...
   * ```message("Project name: ${PROJECT_NAME}")```
   * Note: if you try to use a variable that doesn't exist, it will simply show up as blank
2. Make a simple function to do the same thing but dynamically
   * Syntax: ```function(func_name arg0 ... argN) \n function content \n endfunction()```
   * Child CMakeLists will be able to access functions declared in their parents
   * If there's something you're going to use over and over, probably best to declare it near the top of the project hierarchy
```
function(print var)
    message("${var}: ${${var}}")
endfunction()
```
* This is an example of dereferencing a variable, then dereferencing the dereference.  If you call ```print(PROJECT_NAME)``` the output should be ```PROJECT_NAME = your_project_name```.
* If you take out the "var" argument then you can call the function with multiple args, the function will repeat for each arg provided. In this example you would want to change the function line to ```message("${ARGN}: ${${ARGN}})```. ```ARGC``` is also available, and is the number of arguments sent in. Query specific arguments with ```ARGV0 ... ARGVN```.
3. Looping in functions
```
function(print)
    foreach(var ${ARGN})
        message("${var}: ${${var}}")
    endforeach()
    set(MYVAR "scam")
endfunction()
```
* MYVAR won't be updated outside of this function.
Another useful function...
```
function(print_env)
    foreach(var ${ARGN})
        message("${var}: $ENV{${var}}")
    endforeach()
endfunction()
```
What happens if you change a function to a macro?
   * Macros are similar to functions, but lines inside the macro are inlined at the call site.
   * Be cautious with macros, as they are often defined somewhere far away, not easily referenced. Functions help keep the scope/complexity under control. 
```
macro(print)
    foreach(var ${ARGN})
        message("${var}: ${${var}}")
    endforeach()
    set(MYVAR "not a scam")
endmacro()
```

## Targets
The core of what CMake revolves around.

Targets are things that get compiled and:
   * Properties associated with them
   * Relationships between them

Two main types of targets: executables and libraries
Commands: ```add_executable(...)```, ```add_library(...)```

Libraries can be aliased, similar to typedefs/using in C++:
```add_library(<name> ALIAS <target>)```

Imported libraries - things that aren't built as part of this project
Interface libraries - allow you to create a name to collect a bunch of properties that aren't associated with any .lib, .dll, .a etc. file
Object libraries - not seen too often; they are used to create a list of object files but then don't link them, then you can take that list into another ```add_library``` or ```add_executable``` and it's there that they will be linked. You may need them if you run into issues with the order of linking objects. Behave mostly like libraries. 

Looking at this line:
```target_link_libaries(this_target VISIBILITY)```
There are 3 types of visibility: INTERFACE, PRIVATE, PUBLIC
```INTERFACE``` - any target listed that links this_target is going to be propagated to downstream targets
```PRIVATE``` - these libraries are only used when building this_target, not propagated
```PUBLIC``` - when you build this_target and when consumers link this_target downstream, these properties should be included

## find_package

Goal: finds packages on your system, imports them into your project so you can use them (often libraries). 
Consuming packages found on your system...


