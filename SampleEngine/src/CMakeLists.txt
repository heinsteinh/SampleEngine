cmake_minimum_required(VERSION 3.24)


set(LibName "EngineLib")

project(${LibName} C CXX)


#SET(CMAKE_CXX_STANDARD 17)
#SET(CMAKE_CXX_STANDARD_REQUIRED ON)
#SET(CMAKE_CXX_EXTENSIONS ON)


include_directories(.)
include_directories(${SOURCE_DIR})
include_directories(${INCLUDE_OUTPUT_PATH})


############################## SDL2 #############################################

include(FetchContent)

# Configure SDL
set(SDL_SHARED OFF)
set(SDL_STATIC ON)
set(SDL_TEST_LIBRARY OFF)
set(SDL_INSTALL OFF CACHE BOOL "Disable SDL installation" FORCE)

FetchContent_Declare(SDL2
        GIT_REPOSITORY https://github.com/libsdl-org/SDL.git
        GIT_TAG release-2.30.x
        GIT_SHALLOW ON
        EXCLUDE_FROM_ALL
        SYSTEM)

FetchContent_MakeAvailable(SDL2)



# Collect sources into the variable Engine_Framework_CmdGraphic_Common_Src
#file(GLOB SRC_FILES "florp/src/florp/*.cpp")
#file(GLOB HDR_FILES "florp/include/florp/*.h")
file(GLOB FTS_SOURCE_FILES "*.cpp" "*.h" ${SRC_FILES} ${HDR_FILES})



# Declare use of dependencies
#FetchContent_MakeAvailable(fmt)
#FetchContent_MakeAvailable(spdlog)
#FetchContent_MakeAvailable(stb)
#FetchContent_MakeAvailable(glew)
#FetchContent_MakeAvailable(glm)
#FetchContent_MakeAvailable(imgui)
#add_library(imgui
#    ${imgui_SOURCE_DIR}/imgui.cpp
#    ${imgui_SOURCE_DIR}/imgui_draw.cpp
#    ${imgui_SOURCE_DIR}/imgui_tables.cpp
#    ${imgui_SOURCE_DIR}/imgui_widgets.cpp)
#target_include_directories(imgui PUBLIC ${imgui_SOURCE_DIR})



add_library(${LibName} ${FTS_SOURCE_FILES})


target_include_directories(
    ${LibName}

    PUBLIC
    ${PROJECT_SOURCE_DIR}/include
    # Include configured header file which contains engine metadata
    ${CMAKE_CURRENT_BINARY_DIR}/include/
)



# Include directories
target_include_directories(${LibName}
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
        ${CMAKE_CURRENT_SOURCE_DIR}/src
        ${freetype_SOURCE_DIR}/include
        ${harfbuzz_SOURCE_DIR}/src

        ${glfw_SOURCE_DIR}/include
        ${sdl2_SOURCE_DIR}/include

        ${SDL2_INCLUDE_DIRS}
        ${glfw_INCLUDE_DIR}
)



target_link_libraries(${LibName}
    PUBLIC
    libglew_static
    #spdlog::spdlog_header_only
    SDL2::SDL2main SDL2::SDL2-static
    )


#target_link_libraries(${LibName}
#    PUBLIC
#    fmt::fmt
#    glfw
#    libglew_static
#    glm::glm
#    imgui
#    spdlog::spdlog_header_only
#    tinygltf
#    SDL2::SDL2main SDL2::SDL2-static
#    )   


# Correctly locate SDL2.dll and set up the copy command for Windows
if (WIN32)
    # Copy the SDL2.dll file to the executable directory after build
    add_custom_command(
            TARGET ${LibName} POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_if_different
            $<TARGET_FILE:SDL2::SDL2> $<TARGET_FILE_DIR:${LibName}>
    )
endif()


message(STATUS "IMGUI: ${imgui_SOURCE_DIR}")
message(STATUS "SDL2 SRC: ${sdl2_SOURCE_DIR}")
message(STATUS "STB IMAGE: ${stb_image_SOURCE_DIR}")
message(STATUS "GLEW: ${glew_SOURCE_DIR}")
message(STATUS "GLFW: ${glfw_SOURCE_DIR}")
message(STATUS "GLAD: ${glad_SOURCE_DIR}")
message(STATUS "GLAD Build: ${glad_BUILD_DIR}")