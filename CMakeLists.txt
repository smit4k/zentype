cmake_minimum_required(VERSION 3.15)
project(zentype VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# ────────────────────────────────
# Dependencies
# ────────────────────────────────
find_package(raylib 5.0 QUIET)
if(NOT raylib_FOUND)
    include(FetchContent)
    FetchContent_Declare(raylib
        GIT_REPOSITORY https://github.com/raysan5/raylib.git
        GIT_TAG 5.0
    )
    FetchContent_Declare(raygui
        GIT_REPOSITORY https://github.com/raysan5/raygui.git
        GIT_TAG 4.0
    )
    FetchContent_MakeAvailable(raylib raygui)
else()
    include(FetchContent)
    FetchContent_Declare(raygui
        GIT_REPOSITORY https://github.com/raysan5/raygui.git
        GIT_TAG 4.0
    )
    FetchContent_MakeAvailable(raygui)
endif()

# ────────────────────────────────
# Executable
# ────────────────────────────────
file(GLOB_RECURSE SOURCES "src/*.cpp")
add_executable(${PROJECT_NAME} ${SOURCES})

target_include_directories(${PROJECT_NAME} PRIVATE
    src src/app src/input src/audio
    ${raygui_SOURCE_DIR}/src
)

target_link_libraries(${PROJECT_NAME} PRIVATE raylib)

# Platform-specific
if(APPLE)
    target_link_libraries(${PROJECT_NAME} PRIVATE 
        "-framework IOKit" "-framework Cocoa" 
        "-framework OpenGL" "-framework CoreAudio"
    )
elseif(UNIX)
    target_link_libraries(${PROJECT_NAME} PRIVATE m pthread dl)
endif()

# Compiler warnings
target_compile_options(${PROJECT_NAME} PRIVATE
    $<$<CXX_COMPILER_ID:MSVC>:/W4 /permissive->
    $<$<NOT:$<CXX_COMPILER_ID:MSVC>>:-Wall -Wextra -Wpedantic>
)

# Copy assets
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_SOURCE_DIR}/assets $<TARGET_FILE_DIR:${PROJECT_NAME}>/assets
)