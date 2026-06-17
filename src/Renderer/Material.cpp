#include <Engine/Renderer/Material.h>
#include <Engine/Renderer/Texture.h>

#include <iostream>

Material::Material()
{
}

Material::~Material()
{
}

void Material::Create(std::string name, std::vector<float> Ka, std::vector<float> Kd, std::vector<float> Ks, float Ns, std::string map_Kd, unsigned int textureID)
{
    this->name = name;
    this->Ka = Ka;
    this->Kd = Kd;
    this->Ks = Ks;
    this->Ns = Ns;
    this->map_Kd = map_Kd;
    //this->textureID = textureID;
}

void Material::Init(std::map<std::string, std::vector<std::string>> kMap, std::string name)
{
    this->name = name;
    std::map<std::string, std::vector<std::string>>::iterator aspect = kMap.begin();
    for(; aspect != kMap.end(); ++aspect)
    {
        if(aspect->first == "Ka" || aspect->first == "Kd" || aspect->first == "Ks" || aspect->first == "Ke" || aspect->first == "Tf")
        {
            std::string kType = aspect->first;
            std::vector<std::string> vK = aspect->second;
            SetKVectors(kType, vK);
        }
        else if(aspect->first == "Ns")
        {
            Ns = std::stof(aspect->second[0]);
        }
        else if(aspect->first == "map_Kd")
        {
            map_Kd = aspect->second[0];
        }
    }
}

void Material::SetKVectors(std::string kType, std::vector<std::string> vK)
{
    std::vector<float> fKvector;
    for(int i = 0; i < vK.size(); ++i)
    {
        fKvector.push_back(std::stof(vK[i]));
    }
    if(kType == "Ka")
    {
        Ka = fKvector;
    }
    else if(kType == "Kd")
    {
        Kd = fKvector;
    }
    else if(kType == "Ks")
    {
        Ks = fKvector;
    }
}