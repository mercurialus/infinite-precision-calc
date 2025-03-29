cmake_minimum_required(VERSION 3.14)
project(InfinitePrecisionCalc)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Enable testing
include(CTest)
enable_testing()

# Set output directories
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# Source files
file(GLOB_RECURSE SRC_FILES
    src/*.cpp
)

# Header files (for IDEs)
file(GLOB_RECURSE HEADER_FILES
    src/*.hpp
)

# Main executable
add_executable(infcalc ${SRC_FILES} ${HEADER_FILES})

# Tests
#add_subdirectory(tests)
