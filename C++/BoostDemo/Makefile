CXX = g++
CXXFLAGS_DEBUG = -g -fdiagnostics-color=always
CXXFLAGS_RELEASE = -O3

INCLUDE_DIR = C:/.include/boost_1_82_0
LIB_DIR = C:/.include/boost_1_82_0/lib

LIBS_DEBUG = -lboost_filesystem-mgw13-mt-d-x64-1_82 -lboost_chrono-mgw13-mt-d-x64-1_82
LIBS_RELEASE = -lboost_filesystem-mgw13-mt-x64-1_82 -lboost_chrono-mgw13-mt-x64-1_82

# Can be called "src" "obj" "bin" respectively to look relative to the directory of the makefile
SOURCE_DIR = C:/Users/jacob/Documents/CodingPractice/C++/BoostDemo
OBJECT_DIR = C:/Users/jacob/Documents/CodingPractice/C++/BoostDemo
OUTPUT_DIR = C:/Users/jacob/Documents/CodingPractice/C++/BoostDemo

# Get all .cpp files in the source directory
SOURCES = $(wildcard $(SOURCE_DIR)/*.cpp)

# Generate corresponding .o file names
OBJECTS = $(patsubst $(SOURCE_DIR)/%.cpp,$(OBJECT_DIR)/%.o,$(SOURCES))

# Generate corresponding output executable names
DEBUG_EXECUTABLES = $(patsubst $(SOURCE_DIR)/%.cpp,$(OUTPUT_DIR)/%-debug,$(SOURCES))
RELEASE_EXECUTABLES = $(patsubst $(SOURCE_DIR)/%.cpp,$(OUTPUT_DIR)/%-release,$(SOURCES))

# Default target
all: build

# Build target
build: debug

# Debug target
debug: $(DEBUG_EXECUTABLES)

# Release target
release: $(RELEASE_EXECUTABLES)

# Rule for creating .o files from .cpp files with debug flags
$(OBJECT_DIR)/%-debug.o: $(SOURCE_DIR)/%.cpp
	$(CXX) $(CXXFLAGS_DEBUG) -c $< -o $@ -I$(INCLUDE_DIR)

# Rule for creating executables with debug flags
$(OUTPUT_DIR)/%-debug: $(OBJECT_DIR)/%-debug.o
	$(CXX) $< -o $@ -L$(LIB_DIR) $(LIBS_DEBUG)

# Rule for creating .o files from .cpp files with release flags
$(OBJECT_DIR)/%-release.o: $(SOURCE_DIR)/%.cpp
	$(CXX) $(CXXFLAGS_RELEASE) -c $< -o $@ -I$(INCLUDE_DIR)

# Rule for creating executables with release flags
$(OUTPUT_DIR)/%-release: $(OBJECT_DIR)/%-release.o
	$(CXX) $< -o $@ -L$(LIB_DIR) $(LIBS_RELEASE)

# Clean target
clean:
	rm -rf $(OBJECT_DIR)/*.o $(OUTPUT_DIR)/*

# Phony targets
.PHONY: all build release clean
