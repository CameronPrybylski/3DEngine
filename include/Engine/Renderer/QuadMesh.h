#pragma once

#include <Engine/Renderer/Mesh.h>

class QuadMesh : public Mesh {
public:
    QuadMesh();
    ~QuadMesh();

    virtual void SetVertices(std::vector<float> vertices){}

};