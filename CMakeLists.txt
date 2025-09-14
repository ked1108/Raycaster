cmake_minimum_required(VERSION 3.16)
project(RaycasterEngine)

set(CMAKE_CXX_STANDARD 17)

# GLFW
find_package(glfw3 3.3 REQUIRED)

# GLAD via FetchContent
include(FetchContent)
FetchContent_Declare(
    glad
    GIT_REPOSITORY https://github.com/Dav1dde/glad.git
    GIT_TAG        v0.1.36 
)
FetchContent_MakeAvailable(glad)

# Your sources
add_executable(raycaster
    src/main.cpp
    src/Raycaster.cpp
    src/Player.cpp
    src/Maze.cpp
    src/InputHandler.cpp
)

# Link everything
target_link_libraries(raycaster
    PRIVATE
    glfw
    glad
)

# Include dirs for your project
target_include_directories(raycaster PRIVATE lib)
