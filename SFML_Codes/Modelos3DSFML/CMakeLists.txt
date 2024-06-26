
cmake_minimum_required(VERSION 3.5)  # CMake version check

set(PROJECT_NAME                      # Define all project info
  Models 
  LANGUAGES CXX
  VERSION 1.0.0
)

project(${PROJECT_NAME})              # Create project "Models"

set(CMAKE_CXX_STANDARD 14)            # Enable c++14 standard

set(PROJECT_HEADER                    # Directory of all header file
  src/Sphere/sphere.hpp
  src/Torus/torus.hpp
  src/Rose/rose.hpp
  src/common.hpp
  src/point.hpp
)

set(PROJECT_SOURCE                    # Directory of all source file
  src/Sphere/sphere.cpp
  src/Torus/torus.cpp
  src/Rose/rose.cpp
  src/main.cpp
)

# List all the image files
set(RESOURCES_DIRECTORY 
  "${CMAKE_SOURCE_DIR}/img"
)

# Copy the entire img directory to the binary directory during build
file(COPY ${RESOURCES_DIRECTORY} 
  DESTINATION ${CMAKE_BINARY_DIR}
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

# Specify libraries or flags to use when linking a given target and/or its dependents
target_link_libraries(${PROJECT_NAME}
  PRIVATE sfml-graphics
  PRIVATE sfml-window
  PRIVATE sfml-system
)
