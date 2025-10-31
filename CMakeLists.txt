cmake_minimum_required(VERSION 3.15)
project(zentype VERSION 1.0.0 LANGUAGES CXX)

# ────────────────────────────────
# C++ standard
# ────────────────────────────────
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# ────────────────────────────────
# Output directory
# ────────────────────────────────
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# ────────────────────────────────
# Raylib setup
# ────────────────────────────────
find_package(raylib 5.0 QUIET)
if (NOT raylib_FOUND)
    include(FetchContent)
    FetchContent_Declare(
        raylib
        GIT_REPOSITORY https://github.com/raysan5/raylib.git
        GIT_TAG 5.0
    )
    FetchContent_MakeAvailable(raylib)
endif()

# ────────────────────────────────
# Optional: raygui (GUI library)
# ────────────────────────────────
include(FetchContent)
FetchContent_Declare(
    raygui
    GIT_REPOSITORY https://github.com/raysan5/raygui.git
    GIT_TAG 4.0
)
FetchContent_MakeAvailable(raygui)

# ────────────────────────────────
# Source and header files
# ────────────────────────────────
file(GLOB_RECURSE SOURCES
    "src/*.cpp"
)
file(GLOB_RECURSE HEADERS
    "src/*.h"
    "src/*.hpp"
)

# ────────────────────────────────
# Executable target
# ────────────────────────────────
add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS})

# ────────────────────────────────
# Include directories
# ────────────────────────────────
target_include_directories(${PROJECT_NAME} PRIVATE
    src
    src/app
    src/input
    src/audio
    ${raygui_SOURCE_DIR}/src
)

# ────────────────────────────────
# Link Raylib
# ────────────────────────────────
target_link_libraries(${PROJECT_NAME} PRIVATE raylib)

# ────────────────────────────────
# Copy assets folder after build
# ────────────────────────────────
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_SOURCE_DIR}/assets
    ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/assets
    COMMENT "Copying assets to build directory..."
)

# ────────────────────────────────
# Platform-specific linking
# ────────────────────────────────
if (APPLE)
    target_link_libraries(${PROJECT_NAME} PRIVATE 
        "-framework IOKit" 
        "-framework Cocoa" 
        "-framework OpenGL"
        "-framework CoreAudio"
    )
elseif (UNIX AND NOT APPLE)
    target_link_libraries(${PROJECT_NAME} PRIVATE m pthread dl)
endif()

# ────────────────────────────────
# Compiler warnings
# ────────────────────────────────
if (MSVC)
    target_compile_options(${PROJECT_NAME} PRIVATE /W4 /permissive-)
else()
    target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Wextra -Wpedantic)
endif()