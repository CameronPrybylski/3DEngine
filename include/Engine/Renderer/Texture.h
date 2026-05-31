#pragma once

#include <string>

class Texture
{

public:
    Texture(){}
    Texture(const std::string& filepath);
    ~Texture();

    virtual void Create(const std::string& filepath);
    virtual void Bind(unsigned int slot = 0);
    virtual void Unbind();
    virtual void Delete();

    virtual void PrintID();

protected:
    unsigned int ID;
    unsigned int width, height, BPP;
    std::string filepath;
    unsigned char* localBuffer;

};