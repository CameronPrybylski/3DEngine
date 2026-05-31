#include <Engine/Core/Input.h>

void Input::OnEvent(const SDL_Event& event)
{
    switch (event.type)
    {
    case SDL_KEYDOWN:
        keysDown.insert(event.key.keysym.scancode);
        break;
    case SDL_KEYUP:
        keysDown.erase(event.key.keysym.scancode);
        break;
    case SDL_MOUSEBUTTONDOWN:
        HandleMouseEvents(event);
        break;
     case SDL_MOUSEBUTTONUP:
        HandleMouseEvents(event);
        break;
    case SDL_QUIT:
        shutDown = true;
        break;
    default:
        break;
    }
}

void Input::HandleMouseEvents(const SDL_Event& event)
{

    switch (event.type)
    {
    case SDL_MOUSEBUTTONDOWN:
        if(event.button.button == SDL_BUTTON_LEFT){
            leftMouseClicked = true;
        }
        break;
    case SDL_MOUSEBUTTONUP:
        if(event.button.button == SDL_BUTTON_LEFT){
            leftMouseClicked = false;
        }
        break;
    default:
        break;
    }
    
}

bool Input::IsKeyDown(std::string keyStr) const
{
    SDL_Scancode scanCode = SDL_GetScancodeFromName(keyStr.c_str());
    return keysDown.find(scanCode) != keysDown.end();
}

bool Input::IsLeftMouseButtonDown() const
{
    return leftMouseClicked;
}

bool Input::ShutDown()
{
    return shutDown;
}