#pragma once

#include<Engine/Renderer/Vao.h>
#include<Engine/Renderer/Vbo.h>
#include<Engine/Renderer/Ibo.h>

#include <iostream>


class Mesh {

public:
    Mesh(){
    }
    ~Mesh(){}

    void Bind() const {
        vao.Bind();
        vbo.Bind();
        ibo.Bind();
    }
    void Unbind() const {
        vao.Unbind();
        vbo.Unbind();
        ibo.Unbind();
    }

    void getIDs() const {
        std::cout << vao.getID() << " " << vbo.getID() << " " << ibo.getID() << std::endl;
    }

    int GetIndexCount() const {return ibo.GetIndexCount();}

    virtual void SetVertices(std::vector<float> vertices) = 0;

protected:
    Vao vao;
    Vbo vbo;
    Ibo ibo;

};