cmake_minimum_required(VERSION 3.5)  # CMake version check

set(PROJECT_NAME                      # Define all project info
  EsferaRayTracing
  LANGUAGES CXX
  VERSION 1.0.0
)

project(${PROJECT_NAME})              # Create project "EsferaRayTracing"

set(CMAKE_CXX_STANDARD 17)            # Enable c++11 standard

set(PROJECT_HEADER                    # Directory of all header file
  ../Engine/src/HitTable/hittable_list.hpp
  ../Engine/src/HitTable/hittable.hpp
  ../Engine/include/constante.hpp
  ../Engine/include/material.hpp
  ../Engine/include/texture.hpp
  ../Engine/src/Color/color.hpp
  ../Engine/include/camera.hpp
  ../Engine/include/vec3.hpp 
  ../Engine/include/ray.hpp
  src/Render/render.hpp
  src/Sphere/sphere.hpp
)

set(PROJECT_SOURCE                    # Directory of all source file
  ../Engine/src/HitTable/hittable_list.cpp
  ../Engine/src/Color/color.cpp
  src/Render/render.cpp
  src/Sphere/sphere.cpp
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
