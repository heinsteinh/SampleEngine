
#include <iostream>


#include <GL/glew.h>    // ✅ Must be first
#include <SDL2/SDL.h>   // Or <SDL.h> on Windows
#include <SDL2/SDL_opengl.h>

#include <spdlog/sinks/basic_file_sink.h>
#include <spdlog/sinks/rotating_file_sink.h>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/spdlog.h>


int main(int argc, char *argv[]) {

    spdlog::info("Welcome to spdlog version {}.{}.{}  !", SPDLOG_VER_MAJOR, SPDLOG_VER_MINOR, SPDLOG_VER_PATCH);

    if (SDL_Init(SDL_INIT_VIDEO)) {
        std::cerr << "Error initializing SDL:" << SDL_GetError() << std::endl;
        std::exit(EXIT_FAILURE);
    }

    // Access to OpenGL 4.6
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 0);
    //SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    //SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);


    // Prevent screen flickering
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);


    SDL_Window* window = SDL_CreateWindow("Axis Render", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
         1280, 720, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);

    if (!window) {
        std::cerr << "Failed to creating a window! Error: " << SDL_GetError() << std::endl;
        std::exit(EXIT_FAILURE);
    }

     SDL_GLContext mainContext = SDL_GL_CreateContext(window);

    if (!mainContext) {
        std::cerr << "Error creating context! Error: " << SDL_GetError() << std::endl;
        SDL_DestroyWindow(window);
        SDL_Quit();

        std::exit(EXIT_FAILURE);
    }


    // Check current version of OpenGL
    const GLubyte* version = glGetString(GL_VERSION);
    if (version) {
        std::cout << "OpenGL Version: " << version << std::endl;
    }


        // Get OpenGL version
    const GLubyte* version1 = glGetString(GL_VERSION);
    const GLubyte* vendor = glGetString(GL_VENDOR);
    const GLubyte* renderer = glGetString(GL_RENDERER);

    std::cout << "OpenGL Version: " << version << std::endl;
    std::cout << "Vendor: " << vendor << std::endl;
    std::cout << "Renderer: " << renderer << std::endl;


      // Init GLEW after OpenGL context is created
    GLenum err = glewInit();
    if (GLEW_OK != err) {
        std::cerr << "GLEW Error: " << glewGetErrorString(err) << std::endl;
        return 1;
    }



    SDL_GL_MakeCurrent(window, mainContext);
    SDL_GL_SetSwapInterval(1);


    bool running = true;
    while (running)
    {
        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_KEYDOWN)
            {
                switch (event.key.keysym.sym)
                {
                case SDLK_ESCAPE:
                    running = false;
                    break;
                // Other input here
                default:
                    break;
                }
            }
            else if (event.type == SDL_QUIT)
            {
                running = 0;
            }
        }


        glViewport(0, 0, 640, 480);
        glClearColor(1.f, 0.f, 1.f, 0.f);
        glClear(GL_COLOR_BUFFER_BIT);


        // OpenGL rendering goes here

        SDL_GL_SwapWindow(window);
    }

    // Cleanup and close SDL
    SDL_GL_DeleteContext(mainContext);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}