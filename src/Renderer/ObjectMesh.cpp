#include <Engine/Renderer/ObjectMesh.h>


ObjectMesh::ObjectMesh()
{
}

ObjectMesh::~ObjectMesh()
{}

void ObjectMesh::SetVertInd(std::vector<float> vertices, std::vector<unsigned int> indecies)
{
    
    vao.Create();
    vbo.Create(vertices);
    ibo.Create(indecies);

    vao.Bind();
    vbo.Bind();
    ibo.Bind();

    vao.LinkCubeVbo(vbo, 0);

    vao.Unbind();
    vbo.Unbind();
    ibo.Unbind();
}

void ObjectMesh::SetVertTextInd(std::vector<float> vertices, std::vector<unsigned int> indecies)
{
    
    vao.Create();
    vbo.Create(vertices);
    ibo.Create(indecies);

    vao.Bind();
    vbo.Bind();
    ibo.Bind();

    vao.LinkTextureCubeVbo(vbo, 0);

    vao.Unbind();
    vbo.Unbind();
    ibo.Unbind();
}

void ObjectMesh::SetVertexInd(std::vector<unsigned int> indecies)
{
    vao.Create();
    std::vector<float> vertexes;
    for(auto vertex : vertices)
    {
        vertexes.push_back(vertex.position[0]);
        vertexes.push_back(vertex.position[1]);
        vertexes.push_back(vertex.position[2]);
        vertexes.push_back(vertex.textCoord[0]);
        vertexes.push_back(vertex.textCoord[1]);
    }
    vbo.Create(vertexes);
    ibo.Create(indecies);

    vao.Bind();
    vbo.Bind();
    ibo.Bind();

    vao.LinkTextureCubeVbo(vbo, 0);

    vao.Unbind();
    vbo.Unbind();
    ibo.Unbind();
}