
cmake_minimum_required(VERSION 3.10)
project(MyOpenGLApp LANGUAGES CXX C)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Add glad
add_library(glad src/glad.c)
target_include_directories(glad PUBLIC include)

# Find GLFW
find_package(PkgConfig REQUIRED)
pkg_check_modules(GLFW REQUIRED glfw3)

# Executable
add_executable(graphics 
    src/main.cpp
    src/shader.cpp
    src/texture.cpp
    src/VBO.cpp
    src/VAO.cpp
    src/EBO.cpp
)

# Includes
target_include_directories(graphics PRIVATE include ${GLFW_INCLUDE_DIRS})

# Link libraries
target_link_libraries(graphics PRIVATE glad ${GLFW_LIBRARIES} dl GL)

# Export compile_commands.json for clangd
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
