#include <Engine/Renderer/QuadMesh.h>

QuadMesh::QuadMesh()
{
   std::vector<float> vertices = {
    -0.5f, -0.5f, 0.0f, 0.0f,
     0.5f, -0.5f, 1.0f, 0.0f,
     0.5f,  0.5f, 1.0f, 1.0f,
    -0.5f,  0.5f, 0.0f, 1.0f
};


    std::vector<unsigned int> indices = {
        0, 1, 2,
        2, 3, 0
    };
    
    vao.Create();
    vbo.Create(vertices);
    ibo.Create(indices);

    vao.Bind();
    vbo.Bind();
    ibo.Bind();

    vao.LinkVbo(vbo, 0);

    vao.Unbind();
    vbo.Unbind();
    ibo.Unbind();
}

QuadMesh::~QuadMesh()
{
    
}