#pragma once

#include <string>
#include <vector>
#include <map>

class Texture;

class Material {

public:
    Material();
    ~Material();

    void Create(std::string name, std::vector<float> Ka, std::vector<float> Kd, std::vector<float> Ks, float Ns, std::string map_Kd, unsigned int textureID);
    void Init(std::map<std::string, std::vector<std::string>> kMap, std::string name);

    std::string GetName(){return name;}
    std::string GetMapKd(){return map_Kd;}

    void SetSIndecies(std::vector<std::string> sIndecies){this->sIndecies = sIndecies;}
    void SetUiIndecies(std::vector<unsigned int> uiIndecies){this->uiIndecies = uiIndecies;}

    std::vector<unsigned int> GetUiIndecies(){return this->uiIndecies;}
    void SetStarts(std::vector<int> starts){this->starts = starts;}
    void AddStart(int start){this->starts.push_back(start);}
    std::vector<int> GetStarts(){return this->starts;}


private:
    std::string name;
    std::vector<float> Ka; // Ambient color
    std::vector<float> Kd; // Diffuse color
    std::vector<float> Ks; // Specular color
    std::vector<float> Ke; 
    float Ns;              // Specular exponent (shininess)
    std::string map_Kd;    // Diffuse texture file path

    std::vector<unsigned int> uiIndecies;
    std::vector<std::string> sIndecies;
    std::vector<int> starts;

    void SetKVectors(std::string kType, std::vector<std::string> vK);
    
    //unsigned int textureID;// Loaded GPU texture ID
    //Texture texture;
};