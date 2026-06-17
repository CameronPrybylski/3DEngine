#include <Engine/Renderer/Texture3D.h>
#include <glad/glad.h>
#include <stb_image.h>
#include <iostream>



Texture3D::~Texture3D()
{
    glDeleteTextures(1, &ID);
}

void Texture3D::Create(const std::string &filepath)
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
    depth = 
    BPP = stb_bpp;

    glGenTextures(1, &ID);
    glBindTexture(GL_TEXTURE_3D, ID);
        
    // Set Texture Parameters i for integer
    glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    //S is kinda like X for texures and T is kinda like Y and R is kinda like Z for texures
    glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

    //glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, localBuffer);
    // Upload 3D voxel data (e.g., width = 64, height = 64, depth = 64)
    // Replace 'voxelsData' with your actual raw array pointer
    glTexImage3D(GL_TEXTURE_3D, 0, GL_RGBA8, width, height, 64, 0, GL_RGBA, GL_UNSIGNED_BYTE, localBuffer);

    //Unbind
    glBindTexture(GL_TEXTURE_3D, 0);

    if(localBuffer){
        stbi_image_free(localBuffer);
    }

}

void Texture3D::Bind(unsigned int slot)
{
    glActiveTexture(GL_TEXTURE0 +  slot);
    glBindTexture(GL_TEXTURE_3D, ID);
}

void Texture3D::Unbind()
{
    glBindTexture(GL_TEXTURE_3D, 0);
}
