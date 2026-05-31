#include <Engine/Core/Window.h>
#include <SDL_ttf.h>
#include <iostream>

Window::Window()
{
}

Window::~Window()
{
    TTF_Quit();
    SDL_DestroyWindow(window);
    SDL_Quit();
}

bool Window::Init(const char* title, int width, int height)
{
    if(SDL_Init(SDL_INIT_EVERYTHING) == 0)
    {
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

        window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);
        if(!window)
        {
            std::cerr << "Error creating window" << SDL_GetError() << std::endl;
            return false;
        }

        if (TTF_Init() == -1) {
            std::cerr << "Failed to initialize SDL_ttf: " << TTF_GetError() << std::endl;
        }

        glContext = SDL_GL_CreateContext(window);
        SDL_GL_SetSwapInterval(1);
        int swapInterval = SDL_GL_GetSwapInterval();
        std::cout << "VSync is " << (swapInterval == 1 ? "enabled" : "disabled") << std::endl;


        if (!glContext) {
            std::cerr << "Failed to create GL context: " << SDL_GetError() << std::endl;
            return false;
        }

        // Load OpenGL functions using GLAD
        if (!gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress)) {
            std::cerr << "Failed to initialize GLAD" << std::endl;
            return false;
        }

        std::cout << "Running OpenGL version: " << glGetString(GL_VERSION) << std::endl;

        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        this->width = width;
        this->height = height;
        return true;
    }
    else
    {
        std::cerr << "SDL Failed to init Everything" << std::endl;
        return false;
    }
}

void Window::Update()
{
    SDL_GL_SwapWindow(window);
}

bool Window::ShutDown()
{
    return shouldClose;
}

bool Window::PollEvent(SDL_Event& event)
{
    return SDL_PollEvent(&event);  
}