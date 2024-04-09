# -------------------------------------------------------------------------

# CMake version check
cmake_minimum_required(VERSION 3.4...3.20 FATAL_ERROR)

# -------------------------------------------------------------------------

# Define all project info
set(PROJECT_NAME
  Demo
  LANGUAGES CXX
  VERSION 1.0.0  
)

# Create project "Demo"
project(${PROJECT_NAME})

# Enable c++20 standard
set(CMAKE_CXX_STANDARD 20)

# List all the files
set(RESOURCES_DIRECTORY 
  "${CMAKE_SOURCE_DIR}/obj"
)

file(COPY ${RESOURCES_DIRECTORY} 
  DESTINATION ${CMAKE_BINARY_DIR}
)

# Flags of compiling
add_compile_options(
  -Wall -Wextra -Wpedantic -Werror -pedantic -Wno-unknown-pragmas -g -Ofast
)

add_subdirectory(src)

# -------------------------------------------------------------------------