cmake_minimum_required(VERSION 3.15)
project(zentype VERSION 1.0.0 LANGUAGES CXX)
# Allow older CMake policies so raylib's CMakeLists does not break
cmake_policy(VERSION 3.15...3.27)
set(CMAKE_POLICY_VERSION_MINIMUM 3.5)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# ---------------------------------------------------------
# Detect MinGW Cross-Compilation
# ---------------------------------------------------------
if(CMAKE_CROSSCOMPILING AND MINGW)
    message(STATUS "Cross-compiling for Windows with MinGW")
    set(CROSSCOMPILE_MINGW TRUE)
else()
    set(CROSSCOMPILE_MINGW FALSE)
endif()

# ---------------------------------------------------------
# Dependencies (raylib + raygui) using FetchContent
# ---------------------------------------------------------
include(FetchContent)

# raylib ---------------------------------------------------
FetchContent_Declare(
    raylib
    GIT_REPOSITORY https://github.com/raysan5/raylib.git
    GIT_TAG 5.0
)
set(BUILD_SHARED_LIBS OFF CACHE BOOL "")
set(BUILD_EXAMPLES OFF CACHE BOOL "Disable raylib examples")
FetchContent_MakeAvailable(raylib)

# raygui ---------------------------------------------------
FetchContent_Declare(
    raygui
    GIT_REPOSITORY https://github.com/raysan5/raygui.git
    GIT_TAG 4.0
)
FetchContent_MakeAvailable(raygui)

# ---------------------------------------------------------
# Build executable
# ---------------------------------------------------------
file(GLOB_RECURSE SOURCES "src/*.cpp")
add_executable(${PROJECT_NAME} ${SOURCES})

target_include_directories(${PROJECT_NAME} PRIVATE
    src
    src/app
    src/input
    src/audio
    ${raygui_SOURCE_DIR}/src
)

target_link_libraries(${PROJECT_NAME} PRIVATE raylib)

# ---------------------------------------------------------
# Platform-specific libraries
# ---------------------------------------------------------
if(APPLE)
    target_link_libraries(${PROJECT_NAME} PRIVATE
        "-framework IOKit"
        "-framework Cocoa"
        "-framework OpenGL"
        "-framework CoreAudio"
    )

elseif(UNIX AND NOT MINGW)
    target_link_libraries(${PROJECT_NAME} PRIVATE m pthread dl)

elseif(MINGW)
    target_link_libraries(${PROJECT_NAME} PRIVATE
        winmm
        gdi32
        user32
        shell32
    )
endif()

# ---------------------------------------------------------
# Compiler warnings
# ---------------------------------------------------------
target_compile_options(${PROJECT_NAME} PRIVATE
    $<$<CXX_COMPILER_ID:MSVC>:/W4 /permissive->
    $<$<NOT:$<CXX_COMPILER_ID:MSVC>>:-Wall -Wextra -Wpedantic>
)

# ---------------------------------------------------------
# Copy assets to build output
# ---------------------------------------------------------
add_custom_command(
    TARGET ${PROJECT_NAME} POST_BUILD

    COMMENT "Copying assets folder to output directory..."

    COMMAND ${CMAKE_COMMAND} -E make_directory
        "$<TARGET_FILE_DIR:${PROJECT_NAME}>/assets"

    COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${CMAKE_SOURCE_DIR}/assets"
        "$<TARGET_FILE_DIR:${PROJECT_NAME}>/assets"
)

