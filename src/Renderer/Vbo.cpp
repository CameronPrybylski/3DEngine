#include <Engine/Renderer/Vbo.h>

Vbo::Vbo(){}

Vbo::~Vbo()
{
    glDeleteBuffers(1, &ID);
}

void Vbo::Create(std::vector<float> vertices)
{
    glGenBuffers(1, &ID);
    glBindBuffer(GL_ARRAY_BUFFER, ID);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(), GL_DYNAMIC_DRAW);
}


void Vbo::Bind() const
{
    glBindBuffer(GL_ARRAY_BUFFER, ID);
}

void Vbo::Unbind() const
{
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Vbo::Delete()
{
    glDeleteBuffers(1, &ID);
}