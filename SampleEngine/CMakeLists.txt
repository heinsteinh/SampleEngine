cmake_minimum_required(VERSION 3.24)

project(app-renderer CXX)

SET(CMAKE_CXX_STANDARD 20)
SET(CMAKE_CXX_STANDARD_REQUIRED ON)
SET(CMAKE_CXX_EXTENSIONS ON)


if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug CACHE STRING "Build type: None Debug Release RelWithDebInfo MinSizeRel" FORCE)
endif(NOT CMAKE_BUILD_TYPE)


set_property(GLOBAL PROPERTY USE_FOLDERS ON)

option(BUILD_SHARED_LIBS "Build shared libraries" OFF)

# Options
option(FTS_BUILD_BENCHMARKS "Build benchmarks" OFF)
option(FTS_BUILD_DOC "Build documentation" OFF)
option(FTS_BUILD_EXAMPLE "Build example" OFF)
option(FTS_BUILD_TESTS "Build tests" OFF)
option(FTS_FORCE_COLORED_OUTPUT "Always produce ANSI-colored output (GNU/Clang only)." TRUE)

message(STATUS "FTS_BUILD_BENCHMARKS = ${FTS_BUILD_BENCHMARKS}")
message(STATUS "FTS_BUILD_DOC = ${FTS_BUILD_DOC}")
message(STATUS "FTS_BUILD_EXAMPLE = ${FTS_BUILD_EXAMPLE}")
message(STATUS "FTS_BUILD_TESTS= ${FTS_BUILD_TESTS}")


message(STATUS "CMAKE_VERSION = ${CMAKE_VERSION}")
message(STATUS "CMAKE_GENERATOR = ${CMAKE_GENERATOR}")
message(STATUS "C Compiler executable: ${CMAKE_C_COMPILER}")
message(STATUS "CXX Compiler executable: ${CMAKE_CXX_COMPILER}")
message(STATUS "Linker executable: ${CMAKE_LINKER}")
message(STATUS "Build type: ${CMAKE_BUILD_TYPE}")



# The marked constants in application.hpp will be replaced with the following values
set(FTS_ENGINE_NAME "Wheezy Engine")
set(FTS_APP_NAME "Wheezy renderer example")

set(FTS_ENGINE_VERSION_MAJOR 0)
set(FTS_ENGINE_VERSION_MINOR 1)
set(FTS_ENGINE_VERSION_PATCH 0)

set(FTS_APP_VERSION_MAJOR 0)
set(FTS_APP_VERSION_MINOR 1)
set(FTS_APP_VERSION_PATCH 0)


# -------------------------------
# Build Targets
# -------------------------------
set(WINDOWS WINDOWS)
set(MAC MACOS)
set(LINUX LINUX)

set(PLATFORM_TARGET "")

# -------------------------------
# Find Build Target
# -------------------------------
IF(${CMAKE_HOST_SYSTEM_NAME} STREQUAL "Windows")
    set(PLATFORM_TARGET ${WINDOWS})
ELSEIF(${CMAKE_HOST_SYSTEM_NAME} STREQUAL "Linux")
    set(PLATFORM_TARGET ${LINUX})
ELSEIF(${CMAKE_HOST_SYSTEM_NAME} STREQUAL "Darwin")
    set(PLATFORM_TARGET ${MAC})
ELSE()
    message(FATAL_ERROR "Unsupported platform, configuration will end.")
ENDIF()


# -- config output directories
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    set (EXECUTABLE_OUTPUT_PATH            ${PROJECT_SOURCE_DIR}/Host/bin)
    set (LIBRARY_OUTPUT_PATH               ${PROJECT_SOURCE_DIR}/Host/lib)
    set (INCLUDE_OUTPUT_PATH               ${PROJECT_SOURCE_DIR}/Host/include)

    option(FTS_DEBUG   "Enable FTS_DEBUG"   ON)
    option(NDEBUG   "Enable FTS_DEBUG"   ON)
    option(FTS_IMGUI   "Enable FTS_IMGUI"   ON)
else()
    set (EXECUTABLE_OUTPUT_PATH            ${PROJECT_SOURCE_DIR}/Host/bin)
    set (LIBRARY_OUTPUT_PATH               ${PROJECT_SOURCE_DIR}/Host/lib)
    set (INCLUDE_OUTPUT_PATH               ${PROJECT_SOURCE_DIR}/Host/include)


    option(FTS_DEBUG   "Enable FTS_DEBUG"   OFF)
    option(NDEBUG   "Enable FTS_DEBUG"   OFF)
    option(FTS_IMGUI   "Enable FTS_IMGUI"   OFF)
endif()



#if(WIN32)
#    set(PYTHON_EXECUTABLE "python")
#else()
#    set(PYTHON_EXECUTABLE "python3")
#endif()
#message(STATUS "CMake PYTHON_EXECUTABLE: ${PYTHON_EXECUTABLE}")


# Download dependencies through CMake
#include(cmake/dependencies.cmake)


add_subdirectory(src)


if(FTS_BUILD_EXAMPLE)
    add_subdirectory(apps)
endif()

if(FTS_BUILD_TESTS)
    add_subdirectory(tests)
endif()