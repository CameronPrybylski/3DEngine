#pragma once

#include <Engine/Renderer/Mesh.h>

class ObjectMesh : public Mesh
{

public:
    ObjectMesh();
    ~ObjectMesh();

    virtual void SetVertices(std::vector<float> vertices) override {}
    virtual void SetVertInd(std::vector<float> vertices, std::vector<unsigned int> indecies) override;
    virtual void SetVertTextInd(std::vector<float> vertices, std::vector<unsigned int> indecies) override;

    virtual void SetVertexInd(std::vector<unsigned int> indecies) override;




};