# Define the project for collision-detection

cmake_minimum_required(VERSION 3.24)

project(sdl2-example)

SET(CMAKE_CXX_STANDARD 17)
SET(CMAKE_CXX_STANDARD_REQUIRED ON)
SET(CMAKE_CXX_EXTENSIONS ON)


set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/bin)
option(BUILD_SHARED_LIBS "Build shared libraries" OFF)

# Fetch the source code of SFML
include(FetchContent)

FetchContent_Declare(SDL2
        GIT_REPOSITORY https://github.com/libsdl-org/SDL.git
        GIT_TAG release-2.30.x
        GIT_SHALLOW ON
        EXCLUDE_FROM_ALL
        SYSTEM)
FetchContent_MakeAvailable(SDL2)

############################## glew #############################################

set(glew-cmake_BUILD_SHARED
    OFF
    CACHE BOOL "Disable shared build of glew" FORCE)

FetchContent_Declare(
  glew
  GIT_REPOSITORY https://github.com/Perlmint/glew-cmake.git
  GIT_TAG glew-cmake-2.2.0
  )
FetchContent_MakeAvailable(glew)


# Define the executable target
add_executable(sdl2-example src/main.cpp)
target_include_directories(sdl2-example PRIVATE include)

# Link the correct SDL2 targets (both SDL2 and SDL2main)
target_link_libraries(sdl2-example PRIVATE libglew_static SDL2::SDL2main SDL2::SDL2-static)

# Specify that we're using C++17
target_compile_features(sdl2-example PRIVATE cxx_std_17)

# Correctly locate SDL2.dll and set up the copy command for Windows
if (WIN32)
    # Copy the SDL2.dll file to the executable directory after build
    add_custom_command(
            TARGET sdl2-example POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_if_different
            $<TARGET_FILE:SDL2::SDL2> $<TARGET_FILE_DIR:sdl2-example>
    )
endif()