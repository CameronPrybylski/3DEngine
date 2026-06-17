#pragma once

#include <vector>

class Vertex {

public:
    Vertex(){}
    ~Vertex(){}

    std::vector<float> position;
    std::vector<float> textCoord;
    std::vector<float> normal;

    bool operator<(const Vertex& other) const
    {
        return position < other.position;
    }

    bool operator==(const Vertex& other) const
    {
        return position == other.position && textCoord == other.textCoord;
    }
};