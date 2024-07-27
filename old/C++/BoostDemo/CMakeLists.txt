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
