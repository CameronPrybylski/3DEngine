#pragma once

#include <string>
#include <vector>
#include <map>

class Material;
class Mesh;

class ObjectLoader
{
public:
    ObjectLoader();
    ~ObjectLoader();


    void LoadVertInd(std::string filename, std::string materialFilename = "");
    void LoadVertIndTex(std::string filename, std::string materialFilename);
    void LoadVertFourInd(std::string filename);
    void SetVertexPos();
    void SetIndecies();
    std::vector<float> GetVertexPos()
    {
        return this->fVertices;
    }
    std::vector<unsigned int> GetIndecies()
    {
        return this->uIndecies;
    }
    std::map<std::string, std::shared_ptr<Material>> GetMaterialMap(){return this->materialMap;}
    std::vector<std::shared_ptr<Mesh>> GetSubMeshes(){return this->submeshes;}

private: 

    std::vector<std::string> vertices;
    std::vector<std::string> indecies;
    std::vector<float> fVertices;
    std::vector<unsigned int> uIndecies;
    std::string StripSlash(std::string number);
    void LoadPosText(std::vector<std::string> vertexPos, std::vector<std::string> vertexText, int stride);
    void LoadMatIndecies(std::vector<std::string> vertexPos, std::vector<std::string> verText, std::map<std::string, std::vector<std::string>> mtlIndecies);
    std::vector<float> LoadVertex(std::string index, int count, std::vector<float> values);

    void LoadMaterials(std::string materialFilename);
    std::map<std::string, std::shared_ptr<Material>> materialMap;
    std::vector<std::shared_ptr<Mesh>> submeshes;
    
};