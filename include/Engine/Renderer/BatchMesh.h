#pragma once

#include <Engine/Renderer/Mesh.h>

class BatchMesh : public Mesh {
public:
    BatchMesh();
    ~BatchMesh();

    virtual void SetVertices(std::vector<float> vertices) override;

};