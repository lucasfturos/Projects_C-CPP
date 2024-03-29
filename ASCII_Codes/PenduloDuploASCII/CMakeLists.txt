cmake_minimum_required(VERSION 3.5)  # CMake version check

set(PROJECT_NAME                      # Define all project info
  PenduloDuplo
  LANGUAGES CXX
  VERSION 1.0.0
)

project(${PROJECT_NAME})              # Create project "PenduloDuplo"

set(CMAKE_CXX_STANDARD 11)            # Enable c++11 standard

set(PROJECT_HEADER                    # Directory of all header file
  src/plot/plot.hpp
  src/timer/timer.hpp
  src/pendulo/pendulo.hpp
)

set(PROJECT_SOURCE                    # Directory of all source file
  src/timer/timer.cpp
  src/plot/plot.cpp
  src/pendulo/pendulo.cpp
  src/main.cpp
)

# Add executable target with source and header files listed in PROJECT_HEADER and PROJECT_SOURCE variable
add_executable(${PROJECT_NAME} 
  ${PROJECT_HEADER} 
  ${PROJECT_SOURCE}
)

# Specifies include directories to use when compiling a given target
target_include_directories(${PROJECT_NAME} 
  PRIVATE src
)
