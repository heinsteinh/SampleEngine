
add_executable(app-example main.cpp)

target_link_libraries(app-example PRIVATE EngineLib)

if (APPLE)
    target_link_libraries(app-example PRIVATE SDL2)
elseif(WIN32)
    target_link_libraries(${TARGET} PRIVATE SDL2::SDL2)
    target_link_libraries(${TARGET} PRIVATE SDL2::SDL2main)
else()
    target_link_libraries(app-example PRIVATE ${SDL2_LIBRARIES})
    target_link_libraries(app-example  PUBLIC SDL2 glad glfw)
endif()



# Include directories
target_include_directories(app-example
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/include
        ${CMAKE_CURRENT_SOURCE_DIR}/src
        ${freetype_SOURCE_DIR}/include
        ${harfbuzz_SOURCE_DIR}/src


        ${glfw_SOURCE_DIR}/include
        ${glfw_SOURCE_DIR}
        ${sdl2_SOURCE_DIR}/include
)

target_include_directories(
    app-example

    PUBLIC
    ${PROJECT_SOURCE_DIR}/include
    # Include configured header file which contains engine metadata
    ${CMAKE_CURRENT_BINARY_DIR}/include/

    ${sdl2_SOURCE_DIR}/include
    ${glew_SOURCE_DIR}/include
)

message(STATUS "sdl2: ${sdl2_SOURCE_DIR}")
message(STATUS "glew: ${glew_SOURCE_DIR}")
message(STATUS "GLEW_LIBRARIES: ${GLEW_LIBRARIES}")
message(STATUS "freetype: ${freetype_SOURCE_DIR}")