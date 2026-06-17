#pragma once

#include <Engine/Renderer/Texture.h>

class Texture3D : public Texture
{
public:
    Texture3D(){}
    ~Texture3D();

    virtual void Create(const std::string& filepath) override;
    virtual void Bind(unsigned int slot = 0) override;
    virtual void Unbind() override;
protected:
    unsigned int depth;
};