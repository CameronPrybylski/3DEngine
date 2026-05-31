#pragma once 

#include <Engine/Renderer/Texture.h>
#include <SDL_ttf.h>


class TextTexture : public Texture {

public:

    TextTexture(){}

    void Create(const std::string& filepath, const std::string& text);


private:


};