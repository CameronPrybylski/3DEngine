#include <Engine/Renderer/BatchMesh.h>

BatchMesh::BatchMesh()
{

}

BatchMesh::~BatchMesh()
{
}

void BatchMesh::SetVertices(std::vector<float> vertices)
{
    std::vector<unsigned int> indices; 
    std::vector<unsigned int> firstIndecies = 
    {
        0, 1, 2,
        2, 3, 0
    };


    for(int i = 0; i < vertices.size() / 20; ++i)
    {
        for(int j = 0; j < 6; ++j)
        {
            indices.push_back(firstIndecies[j]);
            firstIndecies[j] += 4;
        }
    }
    
    vao.Create();
    vbo.Create(vertices);
    ibo.Create(indices);

    vao.Bind();
    vbo.Bind();
    ibo.Bind();

    vao.LinkBatchVbo(vbo, 0);

    vao.Unbind();
    vbo.Unbind();
    ibo.Unbind();
}