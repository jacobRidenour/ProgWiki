cmake_minimum_required(VERSION 3.12)

project(Folder2Lib)

#message("Boost include directory: ${Boost_INCLUDE_DIRS}")
#message("Boost library directory: ${Boost_LIBRARY_DIRS}")

# Add library target with source files
add_library(Folder2Lib STATIC file.cpp)

target_include_directories(Folder2Lib PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${Boost_INCLUDE_DIRS})

target_link_libraries(Folder2Lib PUBLIC Boost::serialization Boost::regex)
target_link_directories(Folder2Lib PUBLIC ${Boost_LIBRARY_DIRS})