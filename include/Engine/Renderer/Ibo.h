#pragma once

#include <glad/glad.h>
#include <vector>

class Ibo{

public:
    Ibo();
    ~Ibo();
    void Create(std::vector<unsigned int> indices);
    void Bind()const;
    void Unbind()const;
    void Delete();
    unsigned int getID() const {return ID;}
    int GetIndexCount() const {return indexCount;}

private:
    unsigned int ID;
    int indexCount;


};