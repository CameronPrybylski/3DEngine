#include <Engine/Core/ObjectLoader.h>
#include <Engine/Renderer/Material.h>
#include <Engine/Renderer/ObjectMesh.h>

#include <fstream>
#include <iostream>
#include <sstream>


ObjectLoader::ObjectLoader()
{
}

ObjectLoader::~ObjectLoader()
{
}

void ObjectLoader::LoadVertIndTex(std::string filename, std::string materialFilename)
{
    vertices.clear();
    indecies.clear();
    materialMap.clear();
    LoadMaterials(materialFilename);
    std::ifstream file(filename);
    if(!file.is_open())
    {
        std::cerr << "Error opening Object file" << std::endl;
    }

    std::string line;
    std::vector<std::string> vertexPos;
    std::vector<std::string> vertexTex;
    std::string materialName = "";
    std::map<std::string, std::vector<std::string>> mtlIndecies;
    bool start = false;
    while(std::getline(file, line))
    {
        bool isVertexPos = false;
        bool isIndex = false;
        bool isVertexText = false;
        int textC = 0;
        int stride = 0;
        std::istringstream stream(line);
        std::string word;
        while(stream >> word)
        {
            if(word == "v")
            {
                isVertexPos = true;
            }
            else if(word == "vt")
            {
                isVertexText = true;
            }
            else if(word == "f")
            {
                isIndex = true;
            }
            else if(word == "usemtl")
            {
                stream >> word;
                materialName = word;
                start = true;
            }
            else
            {
                if(isVertexPos)
                {
                    vertexPos.push_back(word);
                }
                else if(isVertexText && textC < 2)
                {
                    vertexTex.push_back(word);
                    ++textC;
                }
                else if(isIndex)
                {
                    mtlIndecies[materialName].push_back(word);
                    indecies.push_back(word);
                }
            }
        }
    }
    
    LoadMatIndecies(vertexPos, vertexTex, mtlIndecies);
    file.close();
}

void ObjectLoader::LoadVertInd(std::string filename, std::string materialFilename)
{
    vertices.clear();
    indecies.clear();
    materialMap.clear();
    std::ifstream file(filename);
    if(!file.is_open())
    {
        std::cerr << "Error opening Object file" << std::endl;
    }

    std::string line;
    std::vector<std::string> vertexPos;
    std::vector<std::string> vertexTex;
    std::string materialName = "";
    std::map<std::string, std::vector<std::string>> mtlIndecies;
    bool start = false;
    while(std::getline(file, line))
    {
        bool isVertexPos = false;
        bool isIndex = false;
        bool isVertexText = false;
        int stride = 0;
        std::istringstream stream(line);
        std::string word;
        while(stream >> word)
        {
            if(word == "v")
            {
                isVertexPos = true;
            }
            else if(word == "vt")
            {
                isVertexText = true;
            }
            else if(word == "f")
            {
                isIndex = true;
            }
            else if(word == "usemtl")
            {
                stream >> word;
                materialName = word;
            }
            else
            {
                if(isVertexPos)
                {
                    vertexPos.push_back(word);
                }
                else if(isVertexText)
                {
                    vertexTex.push_back(word);
                }
                else if(isIndex)
                {
                    word = StripSlash(word);
                    indecies.push_back(word);
                }
            }
        }
    }
    
    vertices = vertexPos;
    file.close();
    SetVertexPos();
    SetIndecies();
}

void ObjectLoader::LoadMaterials(std::string materialFilename)
{
    std::ifstream file(materialFilename);
    if(!file.is_open())
    {
        std::cerr << "Error opening Material file" << std::endl;
    }

    std::string line;
    std::string materialName = "";
    std::vector<std::string> Ka; 
    std::vector<std::string> Kd; 
    std::vector<std::string> Ks; 
    std::vector<std::string> Ke; 
    std::map<std::string, std::vector<std::string>> kMap = {
        {"Ka", Ka},
        {"Kd" , Kd},
        {"Ks", Ks},
        {"Ke", Ke}
    };
    while(std::getline(file, line))
    {
        std::istringstream stream(line);
        std::string word;
        while(stream >> word)
        {
            if(word == "newmtl")
            {
                if(materialName != "")
                {
                    materialMap[materialName]->Init(kMap, materialName);
                    kMap.clear();
                }
                materialName = "";
                stream >> materialName;
                materialMap[materialName] = std::make_shared<Material>();
                break;
            }
            else if(word == "Ka" || word == "Kd" || word == "Ks" || word == "Ke" || word == "Tf")
            {
                std::string value;
                while(stream >> value)
                {
                    kMap[word].push_back(value);
                }
            }
            else
            {
                std::string value;
                stream >> value;
                kMap[word] = {value};
            }
        }
    }
    if(materialName != "")
    {
        materialMap[materialName]->Init(kMap, materialName);
    }
}

void ObjectLoader::LoadPosText(std::vector<std::string> vertexPos, std::vector<std::string> vertexText, int stride)
{
    int i = 0;
    int j = 0;
    int start = 0;
    while(i < vertexPos.size() && j < vertexText.size())
    {
        if(start < stride)
        {
            vertices.push_back(vertexPos[i]);
            ++start;
            ++i;
        }
        else if(start < stride * 2)
        {
            vertices.push_back(vertexText[j]);
            ++start;
            ++j;
        }
        else
        {
            start = 0;
        }
    }
}

void ObjectLoader::LoadMatIndecies(std::vector<std::string> vertexPos, std::vector<std::string> verText, std::map<std::string, std::vector<std::string>> mtlIndecies)
{
    std::map<std::string, std::vector<unsigned int>> mtlUiIndecies;
    std::vector<Vertex> vertexes;
    std::vector<float> positions;
    std::vector<float> textcoords;
    fVertices.clear();
    for(int i = 0; i < vertexPos.size(); ++i)
    {
       float v = std::stof(vertexPos[i]);
       positions.push_back(v);
    }
    
    for(int i = 0; i < verText.size(); ++i)
    {
        float vt = std::stof(verText[i]);
        textcoords.push_back(vt);
    }

    std::vector<std::shared_ptr<Mesh>> subMeshes;
    std::map<std::string, std::vector<std::string>>::iterator itr = mtlIndecies.begin();
    for(; itr != mtlIndecies.end(); ++itr)
    {
        std::string materialName = itr->first;
        std::map<Vertex, unsigned int> vertexInd;
        std::vector<unsigned int> indecies;
        std::vector<Vertex> vertices;
        for(int i = 0; i < itr->second.size(); ++i)
        {
            Vertex vertex;
            std::string group = itr->second[i];
            std::stringstream sub_stream(group);
            std::string element;
            int position = 1;
            while (std::getline(sub_stream, element, '/')) 
            {
                if(!element.empty() && position == 1)
                {
                    vertex.position = LoadVertex(element, 3, positions);
                }
                else if(!element.empty() && position == 2)
                {
                    vertex.textCoord = LoadVertex(element, 2, textcoords);
                    break;
                }
                ++position;
            }
            
            if(vertexInd.count(vertex))
            {
                indecies.push_back(vertexInd[vertex]);
            }
            else
            {
                unsigned int newIndex = vertices.size();
                indecies.push_back(newIndex);
                vertexInd[vertex] = newIndex;
                vertices.push_back(vertex);
            }
        }
        std::shared_ptr<ObjectMesh> subMesh = std::make_shared<ObjectMesh>();
        subMesh->vertices = vertices;
        subMesh->SetVertexInd(indecies);
        subMesh->material = materialMap[materialName];
        subMeshes.push_back(subMesh);
    }
    this->submeshes = subMeshes;
}

std::vector<float> ObjectLoader::LoadVertex(std::string index, int count, std::vector<float> values)
{
    unsigned int ind = (unsigned int)std::stoi(index);
    ind -= 1;
    std::vector<float> v;
    int start = ind * count;
    int end = start + count;
    for(int k = start; k < end; ++k)
    {
        v.push_back(values[k]);
    }
    return v;
}

void ObjectLoader::LoadVertFourInd(std::string filename)
{

    vertices.clear();
    indecies.clear();
    std::ifstream file(filename);
    if(!file.is_open())
    {
        std::cerr << "Error opening Object file" << std::endl;
    }

    std::string line;
    while(std::getline(file, line))
    {
        bool isVertex = false;
        bool isIndex = false;
        if(line.length() > 1 && line[0] == 'v' && (line[1] != 'n' || line[1] != 't'))
        {
            isVertex = true;
        }
        else if(line.length() > 0 && line[0] == 'f')
        {
            isIndex = true;
        }
        std::string vertex = "";
        std::string index = "";
        std::vector<std::string> fourIndecies;
        bool conatinsSlash = false;
        bool wait = false;
        int i = 2;
        if(isVertex)
        {
            i = 2;
        }
        for(; i < line.length(); ++i)
        {
            if(isVertex && line[i] != ' ')
            {
                vertex += line[i];
            }
            else if(isVertex && line[i] == ' ')
            {
                if(vertex.length() > 0)
                    vertices.push_back(vertex);
                vertex = "";
            }
            else if(isIndex && line[i] != ' ')
            {
                index += line[i];
            }
            else if(isIndex && line[i] == ' ')
            {
                index = StripSlash(index);
                if(index != " ")
                {
                    fourIndecies.push_back(index);
                }
                index = "";
            }
        }
        if(isVertex)
        {
            if(vertex != "")
                vertices.push_back(vertex);
        }
        else if(isIndex)
        {
            if(fourIndecies.size() == 3)
            {
                index = StripSlash(index);
                fourIndecies.push_back(index);
            }
            if(fourIndecies.size() == 4)
            {
                std::vector<int> firstIndecies {
                    0, 1, 2,
                    2, 3, 0
                };
                for(int i = 0; i < firstIndecies.size(); ++i)
                {
                    indecies.push_back(fourIndecies[firstIndecies[i]]);
                }
            }
        }
    }
    file.close();
    SetVertexPos();
    SetIndecies();
}

void ObjectLoader::SetVertexPos()
{
   fVertices.clear();
   for(int i = 0; i < vertices.size(); ++i)
   {
        float v = std::stof(vertices[i]);
        fVertices.push_back(v);
   }
}

void ObjectLoader::SetIndecies()
{
    uIndecies.clear();
    for(int i = 0; i < indecies.size(); ++i)
    {
        unsigned int ind = (unsigned int)std::stoi(indecies[i]);
        uIndecies.push_back(ind-1);
    }
}

std::string ObjectLoader::StripSlash(std::string number)
{
    std::string stripped = "";
    for(int i = 0; i < number.length(); ++i)
    {
        if(number[i] != '/')
        {
            stripped += number[i];
        }
        else
        {
            break;
        }
    }
    return stripped;
}
