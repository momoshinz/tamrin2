cmake_minimum_required(VERSION 3.10)

# Project name
project(SimpleCppProject)

# C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Add the include directory for header files
include_directories(include)

# Define source files
set(SOURCES
    src/main.cpp
    src/amin.cpp
    src/danny.cpp
    src/doctorWhite.cpp
    src/game.cpp
    src/hero.cpp
    src/tahaB.cpp
    src/tahaK.cpp
    src/team.cpp
)

# Build the executable
add_executable(tamrin2 ${SOURCES})

