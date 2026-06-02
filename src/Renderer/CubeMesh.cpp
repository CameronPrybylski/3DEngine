#include <Engine/Renderer/CubeMesh.h>


CubeMesh::CubeMesh()
{
    std::vector<float> vertices = 
    {
        -0.5f, -0.5f, -0.5f,
        0.5f, -0.5f,  -0.5f,
        0.5f,  0.5f,  -0.5f,
        -0.5f,  0.5f,  -0.5f,

        -0.5f, -0.5f, 0.5f,
        0.5f, -0.5f,  0.5f,
        0.5f,  0.5f,  0.5f,
        -0.5f,  0.5f,  0.5f
    };

    std::vector<unsigned int> firstIndices = {
        0, 1, 2,
        2, 3, 0,
    };

    std::vector<unsigned int> indices
    {
        0, 1, 2,  2, 3, 0, // Front
        1, 5, 6,  6, 2, 1, // Right
        7, 6, 5,  5, 4, 7, // Back
        4, 0, 3,  3, 7, 4, // Left
        4, 5, 1,  1, 0, 4, // Bottom
        3, 2, 6,  6, 7, 3  // Top
    };

    
    
    vao.Create();
    vbo.Create(vertices);
    ibo.Create(indices);

    vao.Bind();
    vbo.Bind();
    ibo.Bind();

    vao.LinkCubeVbo(vbo, 0);

    vao.Unbind();
    vbo.Unbind();
    ibo.Unbind();
}

CubeMesh::~CubeMesh()
{
}