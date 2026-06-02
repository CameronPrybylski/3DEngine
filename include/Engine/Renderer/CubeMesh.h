#pragma once

#include <Engine/Renderer/Mesh.h>

class CubeMesh : public Mesh {
public:
    CubeMesh();
    ~CubeMesh();

    virtual void SetVertices(std::vector<float> vertices){}

};