#include <Engine/Renderer/TextTexture.h>
#include <glad/glad.h>

#include <iostream>

void TextTexture::Create(const std::string& filepath, const std::string& text)
{
    TTF_Font* font = TTF_OpenFont(filepath.c_str(), 72);
    if (!font) {
        std::cerr << "TTF_OpenFont Error: " << TTF_GetError() << std::endl;
        return;
    }

    SDL_Color color = {255, 255, 255, 255};
    SDL_Surface* surface = TTF_RenderText_Blended(font, text.c_str(), color);
    if (!surface) {
        std::cerr << "TTF_RenderText Error: " << TTF_GetError() << std::endl;
        TTF_CloseFont(font);
        return;
    }
    
    // Flip into a new buffer (we’ll just allocate raw memory instead of SDL_Surface)
    Uint8* flippedPixels = new Uint8[surface->h * surface->pitch];
    for (int y = 0; y < surface->h; y++) {
        memcpy(flippedPixels + y * surface->pitch,
               (Uint8*)surface->pixels + (surface->h - 1 - y) * surface->pitch,
               surface->pitch);
    }

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glGenTextures(1, &ID);
    glBindTexture(GL_TEXTURE_2D, ID);

    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    glPixelStorei(GL_UNPACK_ROW_LENGTH, surface->pitch / surface->format->BytesPerPixel);

    GLenum format = (surface->format->Rmask == 0x000000ff) ? GL_RGBA : GL_BGRA;

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA,
                 surface->w, surface->h,
                 0, format, GL_UNSIGNED_BYTE, flippedPixels);

    glPixelStorei(GL_UNPACK_ROW_LENGTH, 0);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glBindTexture(GL_TEXTURE_2D, 0);

    // Clean up
    delete[] flippedPixels;
    SDL_FreeSurface(surface);
    TTF_CloseFont(font);
}