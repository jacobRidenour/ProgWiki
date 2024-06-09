cmake_minimum_required(VERSION 3.12)
project(YourProjectName VERSION 1.0.0)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

#set(Boost_USE_STATIC_LIBS OFF) 
#set(Boost_USE_STATIC_RUNTIME OFF) 
set(Boost_USE_MULTITHREADED ON)  
set(Boost_NO_WARN_NEW_VERSIONS 1)


if(NOT DEFINED BOOST_ROOT)
    set(BOOST_ROOT $ENV{BOOST_ROOT})
endif()

set(CMAKE_PREFIX_PATH "${CMAKE_PREFIX_PATH};${BOOST_ROOT}/stage/lib/cmake/Boost-1.85.0")
set(Boost_DIR "${BOOST_ROOT}/stage/lib/cmake/Boost-1.85.0")

#find_package(Boost 1.85.0 REQUIRED COMPONENTS system chrono thread filesystem)
#find_package(Boost 1.85.0 REQUIRED CONFIG)
find_package(Boost 1.85.0 REQUIRED COMPONENTS thread chrono serialization regex)

message("Boost include directory: ${Boost_INCLUDE_DIRS}")
message("Boost library directory: ${Boost_LIBRARY_DIRS}")

# Include the subdirectories containing the other CMakeLists.txt files
add_subdirectory(folder1)
add_subdirectory(folder2)

# Create the DLL target; link static libs to it & necessary Boost libraries to it
# Add dummy.cpp file to appease CMake
add_library(MyProjectDLL SHARED dummy.cpp)
target_link_libraries(MyProjectDLL PRIVATE
    Folder1Lib Folder2Lib
    Boost::serialization
    Boost::regex
    Boost::thread  
    Boost::chrono
    )

target_include_directories(MyProjectDLL PRIVATE 
    ${Boost_INCLUDE_DIRS}
    "${CMAKE_CURRENT_SOURCE_DIR}") 


# Link directories for the MyProjectDLL target
target_link_directories(MyProjectDLL PRIVATE
    ${Boost_LIBRARY_DIRS})

# Include/link directories (global)
#include_directories(Boost_HOME)
#link_directories(Boost_LIB_DIR)

# cd build
# cmake ..
# cmake --build .