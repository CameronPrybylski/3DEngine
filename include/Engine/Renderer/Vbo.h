#pragma once

#include <glad/glad.h>
#include <vector>


class Vbo {

public:
    Vbo();
    ~Vbo();
    void Create(std::vector<float> vertices);
    void Bind()const;
    void Unbind()const;
    void Delete();
    unsigned int getID() const {return ID;}

private:
    unsigned int ID;

};