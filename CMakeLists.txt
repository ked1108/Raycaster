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

FetchContent_Declare(
    imgui
    GIT_REPOSITORY https://github.com/ocornut/imgui.git
    GIT_TAG        v1.91.0   # pick a stable release
)
FetchContent_MakeAvailable(imgui)

# Your sources
add_executable(raycaster
    src/main.cpp
    src/Raycaster.cpp
    src/Player.cpp
    src/Maze.cpp
    src/InputHandler.cpp
    src/Config.cpp
)

# Link everything
target_link_libraries(raycaster
    PRIVATE
    glfw
    glad
)

target_sources(raycaster PRIVATE
    ${imgui_SOURCE_DIR}/imgui.cpp
    ${imgui_SOURCE_DIR}/imgui_draw.cpp
    ${imgui_SOURCE_DIR}/imgui_widgets.cpp
    ${imgui_SOURCE_DIR}/imgui_tables.cpp
    ${imgui_SOURCE_DIR}/backends/imgui_impl_glfw.cpp
    ${imgui_SOURCE_DIR}/backends/imgui_impl_opengl3.cpp
)
target_include_directories(raycaster PRIVATE
    ${imgui_SOURCE_DIR}
    ${imgui_SOURCE_DIR}/backends
)

# Include dirs for your project
target_include_directories(raycaster PRIVATE lib)
