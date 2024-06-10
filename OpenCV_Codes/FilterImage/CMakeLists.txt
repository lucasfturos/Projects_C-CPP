# -------------------------------------------------------------------

cmake_minimum_required(VERSION 3.5)  # CMake version check

# --- Project settings ----------------------------------------------

set(PROJECT_NAME                      # Define all project info
  FilterImage 
  LANGUAGES CXX
  VERSION 1.0.0
)

project(${PROJECT_NAME})              # Create project 

set(CMAKE_CXX_STANDARD 20)            # Enable c++20 standard

set(PROJECT_SOURCE                    # Directory of all source file
  # main
  src/main.cpp 
)

# Flags of compiling
add_compile_options(
  -Wall -Wextra -Wpedantic -Werror -pedantic -g -Ofast
)

find_package(OpenCV REQUIRED)

add_executable(${PROJECT_NAME} 
  ${PROJECT_SOURCE}
)

target_link_libraries(${PROJECT_NAME}
  PRIVATE ${OpenCV_LIBS} 
)

# -------------------------------------------------------------------
