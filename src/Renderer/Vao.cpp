#include <Engine/Renderer/Vao.h>

Vao::Vao()
{
}

Vao::~Vao()
{
    glDeleteVertexArrays(1, &ID);
}

void Vao::Create()
{
    glGenVertexArrays(1, &ID);
    glBindVertexArray(ID);
}

void Vao::LinkVbo(Vbo& vbo, unsigned int layout)
{
    vbo.Bind();
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*) 0); // Position Coord
    
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*) (2 * sizeof(float))); // Texture Coord
    
    /*
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 4, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)( 4 * sizeof(float))); // color Coord
    */
    vbo.Unbind();
}

void Vao::LinkBatchVbo(Vbo& vbo, unsigned int layout)
{
    vbo.Bind();
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*) 0); // Position Coord
    
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*) (2 * sizeof(float))); // Texture Coord

    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*) (4 * sizeof(float))); // Texture Index
    
    vbo.Unbind();
}

void Vao::Bind() const
{
    glBindVertexArray(ID);
}

void Vao::Unbind() const
{
    glBindVertexArray(0);
}

void Vao::Delete()
{
    glDeleteVertexArrays(1, &ID);
}