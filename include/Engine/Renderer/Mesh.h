#pragma once

#include<Engine/Renderer/Vao.h>
#include<Engine/Renderer/Vbo.h>
#include<Engine/Renderer/Ibo.h>

#include <Engine/Renderer/Vertex.h>
#include <Engine/Renderer/Material.h>

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

    void SetIbo(std::vector<unsigned int> indecies){
        ibo.Unbind();
        ibo.Delete();
        ibo.Create(indecies);
    }

    int GetIndexCount() const {return ibo.GetIndexCount();}

    virtual void SetVertices(std::vector<float> vertices) = 0;
    virtual void SetVertInd(std::vector<float> vertices, std::vector<unsigned int> indecies) = 0;
    virtual void SetVertTextInd(std::vector<float> vertices, std::vector<unsigned int> indecies) = 0;

    virtual void SetVertexInd(std::vector<unsigned int> indecies) = 0;

    std::vector<Vertex> vertices;
    std::shared_ptr<Material> material;


protected:
    Vao vao;
    Vbo vbo;
    Ibo ibo;

};