# -------------------------------------------------------------------------

# List all the header files in the src directory
set(SRC_HEADERS
    # Matrix/matrix.hpp
    ReadObjectFile/read_object_file.cpp
    Render/render.hpp
    Torus/torus.hpp
    Vec3/vec3.hpp
)

# List all the source files in the src directory
set(SRC_SOURCES
    # Matrix/matrix.cpp
    ReadObjectFile/read_object_file.cpp
    Render/render.cpp
    Torus/torus.cpp
    Vec3/vec3.cpp
    main.cpp
)

# Find Threads library
find_package(Threads REQUIRED)

# Add executable target with source and header files
add_executable(${PROJECT_NAME} 
    ${SRC_HEADERS} 
    ${SRC_SOURCES}
)

# Specifies include directories to use when compiling a given target
target_include_directories(${PROJECT_NAME} 
    PRIVATE src 
)

# Specify libraries or flags to use when linking
target_link_libraries(${PROJECT_NAME}
    # Threads
    PRIVATE Threads::Threads
)

# -------------------------------------------------------------------------