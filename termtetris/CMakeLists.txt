cmake_minimum_required(VERSION 3.5)  # CMake version check

set(PROJECT_NAME                      # Define all project info
  TermTetris
  LANGUAGES CXX
  VERSION 1.0.0
)

project(${PROJECT_NAME})              # Create project "termtetris"

set(CMAKE_CXX_STANDARD 17)            # Enable c++17 standard

set(PROJECT_HEADER                    # Directory of all header file
  src/TermTetris/termtetris.hpp
)

set(PROJECT_SOURCE                    # Directory of all source file
  src/TermTetris/termtetris.cpp
  src/main.cpp
)

# Add executable target with source and header files listed in PROJECT_HEADER and PROJECT_SOURCE variable
add_executable(${PROJECT_NAME} 
  ${PROJECT_HEADER} 
  ${PROJECT_SOURCE}
)

# Specifies include directories to use when compiling a given target
target_include_directories(${PROJECT_NAME} 
  PRIVATE src includes
)
