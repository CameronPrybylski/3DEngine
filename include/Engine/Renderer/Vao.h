#pragma once

#include <glad/glad.h>
#include <Engine/Renderer/Vbo.h>

class Vao {

public:
    Vao();
    ~Vao();
    void Create();
    void LinkVbo(Vbo& vbo, unsigned int layout);
    void LinkBatchVbo(Vbo& vbo, unsigned int layout);
    void LinkCubeVbo(Vbo& vbo, unsigned int layout);
    void Bind() const;
    void Unbind() const;
    void Delete();
    unsigned int getID() const {return ID;}

private:
    unsigned int ID;

};