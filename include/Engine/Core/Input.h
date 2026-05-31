#pragma once

#include <SDL.h>
#include <unordered_set>
#include <string>

class Input {

public:

    void OnEvent(const SDL_Event& event);
    void HandleMouseEvents(const SDL_Event& event);
    bool IsKeyDown(std::string keyStr) const;
    bool IsLeftMouseButtonDown() const;
    bool ShutDown();

private:
    std::unordered_set<SDL_Scancode> keysDown;
    bool leftMouseClicked = false;
    bool shutDown = false;


};