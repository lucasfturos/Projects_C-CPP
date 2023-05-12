cmake_minimum_required(VERSION 3.5)  # CMake version check

# --- Project settings ---------------------------------------------------------

set(PROJECT_NAME                      # Define all project info
  CornellBoxRayTracing
  LANGUAGES CXX
  VERSION 1.0.0
)

project(${PROJECT_NAME})              # Create project "CornellBoxRayTracing"

set(CMAKE_CXX_STANDARD 17)            # Enable c++11 standard

set(PROJECT_HEADER                    # Directory of all header file
  ../Engine/src/Constant_Medium/constant_medium.hpp
  ../Engine/src/HitTable/hittable_list.hpp
  ../Engine/src/HitTable/hittable.hpp
  ../Engine/src/Texture/texture.hpp
  ../Engine/include/constante.hpp
  ../Engine/src/Sphere/sphere.hpp
  ../Engine/include/material.hpp
  ../Engine/src/Color/color.hpp
  ../Engine/include/camera.hpp
  ../Engine/src/Rect/rect.hpp
  ../Engine/include/aabb.hpp
  ../Engine/include/vec3.hpp 
  ../Engine/src/Box/box.hpp
  ../Engine/include/ray.hpp
  src/Render/render.hpp
)

set(PROJECT_SOURCE                    # Directory of all source file
  ../Engine/src/Constant_Medium/constant_medium.cpp
  ../Engine/src/HitTable/hittable_list.cpp
  ../Engine/src/HitTable/hittable.cpp
  ../Engine/src/Texture/texture.cpp
  ../Engine/src/Sphere/sphere.cpp
  ../Engine/src/Color/color.cpp
  ../Engine/src/Rect/rect.cpp
  ../Engine/src/Box/box.cpp
  src/Render/render.cpp
  src/main.cpp 
)

# Add executable target with source and header files listed in 
# PROJECT_HEADER and PROJECT_SOURCE variable
add_executable(${PROJECT_NAME} 
  ${PROJECT_HEADER} 
  ${PROJECT_SOURCE}
)

# Specifies include directories to use when compiling a given target
target_include_directories(${PROJECT_NAME} 
  PRIVATE src
  PRIVATE ../Engine/include
)

# ------------------------------------------------------------------------------
