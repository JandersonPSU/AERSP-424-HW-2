# Minimum version of CMake required
cmake_minimum_required(VERSION 3.10)

# Project name and language
project(RobotsProject LANGUAGES CXX)

# Set the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Add source files to the project
set(SOURCES
    main.cpp
    tool.cpp
    robot.cpp
)

# Create the executable
add_executable(robots ${SOURCES})

# Set compiler flags (optional)
if(MSVC)
    target_compile_options(robots PRIVATE /W4) # Enable warnings in MSVC
else()
    target_compile_options(robots PRIVATE -Wall -Wextra -pedantic) # Other compilers
endif()
