cmake_minimum_required(VERSION 3.10)
project(Calculator)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# GoogleTest setup
include(FetchContent)
FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/refs/tags/v1.14.0.zip
)
# Configure GoogleTest build options
set(BUILD_GMOCK OFF CACHE BOOL "" FORCE)
set(INSTALL_GTEST OFF CACHE BOOL "" FORCE)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

# Make GoogleTest available
FetchContent_MakeAvailable(googletest)

# Include directories
include_directories(${CMAKE_SOURCE_DIR})

# Source files
set(SOURCE_FILES
    parser.cpp
    parser.h
)

# Main calculator executable
add_executable(Calculator 
    main.cpp
    ${SOURCE_FILES}
)

# Test files
set(TEST_FILES
    test_main.cpp
    TestSum.cpp
    TestSubtract.cpp
    TestMultiply.cpp
    TestDivide.cpp
    TestComplex.cpp
)

# Test executable
add_executable(CalculatorTests
    ${TEST_FILES}
    ${SOURCE_FILES}
)

# Link test executable with Google Test
target_link_libraries(CalculatorTests PRIVATE
    gtest
    gtest_main
)

# Enable testing
enable_testing()

# Add test
add_test(NAME CalculatorTests COMMAND CalculatorTests)