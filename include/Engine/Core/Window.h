#pragma once

#include <SDL.h>
#include <glad/glad.h>

class Window {

public:
    Window();
    ~Window();

    bool Init(const char* title, int width, int height);
    void Update();
    bool ShutDown();
    bool PollEvent(SDL_Event& event);

    int getWidth(){return width;}
    int getHeight(){return height;}

private:
    SDL_Window* window;
    SDL_GLContext glContext;

    int width;
    int height;

    bool shouldClose = false;

};