#include <Engine/Renderer/Texture.h>
#include <glad/glad.h>
#include <stb_image.h>
#include <iostream>

Texture::Texture(const std::string &filepath) : filepath(filepath), ID(0), width(0), height(0), BPP(0)
{
    stbi_set_flip_vertically_on_load(1);
    //Modiefies the width, height and BPP by passing by reference
    //desiredChannels = 4 for RGBA Red Green Blue Alpha
    int desiredChannels = 4;
    int stb_w, stb_h, stb_bpp;

    localBuffer = stbi_load(filepath.c_str(), &stb_w, &stb_h, &stb_bpp, desiredChannels);
    if(localBuffer == nullptr)
    {
        std::cerr << "Failed to Load image" << std::endl;
    }
    width = stb_w;
    height = stb_h;
    BPP = stb_bpp;

    glGenTextures(1, &ID);
    glBindTexture(GL_TEXTURE_2D, ID);
    
    // Set Texture Parameters i for integer
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    //S is kinda like X for texures and T is kinda like Y for texures
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, localBuffer);

    //Unbind
    glBindTexture(GL_TEXTURE_2D, 0);

    if(localBuffer){
        stbi_image_free(localBuffer);
    }


}

Texture::~Texture()
{
    glDeleteTextures(1, &ID);
}

void Texture::Create(const std::string &filepath)
{
 
    stbi_set_flip_vertically_on_load(1);
    //Modiefies the width, height and BPP by passing by reference
    //desiredChannels = 4 for RGBA Red Green Blue Alpha
    int desiredChannels = 4;
    int stb_w, stb_h, stb_bpp;

    localBuffer = stbi_load(filepath.c_str(), &stb_w, &stb_h, &stb_bpp, desiredChannels);
    if(localBuffer == nullptr)
    {
        std::cerr << "Failed to Load image" << std::endl;
        std::cerr << "stb_image failed: " << stbi_failure_reason() << std::endl;
    }
    width = stb_w;
    height = stb_h;
    BPP = stb_bpp;

    glGenTextures(1, &ID);
    glBindTexture(GL_TEXTURE_2D, ID);
        
    // Set Texture Parameters i for integer
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    //S is kinda like X for texures and T is kinda like Y for texures
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, localBuffer);

    //Unbind
    glBindTexture(GL_TEXTURE_2D, 0);

    if(localBuffer){
        stbi_image_free(localBuffer);
    }

}

void Texture::Bind(unsigned int slot)
{
    glActiveTexture(GL_TEXTURE0 +  slot);
    glBindTexture(GL_TEXTURE_2D, ID);
}

void Texture::Unbind()
{
    glBindTexture(GL_TEXTURE_2D, 0);
}

void Texture::Delete()
{
    glDeleteTextures(1, &ID);
}

void Texture::PrintID()
{
    std::cout << "Texture ID: " << ID << std::endl;
}