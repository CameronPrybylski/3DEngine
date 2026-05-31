#pragma once

#include <Engine/Renderer/Shader.h>
#include <Engine/Renderer/QuadMesh.h>

#include <memory>

class AssetManager{
public:
    static Shader& LoadShader(const std::string& name, const char* vsPath, const char* fsPath) {
        shaders[name] = std::make_shared<Shader>(vsPath, fsPath);
        return *shaders[name];
    }

    static Shader& GetShader(const std::string& name) {
        return *shaders.at(name);
    }

    static void ClearShaders() {
        shaders.clear(); // optionally call Delete() on each Shader
    }

    static Mesh& LoadMesh(const std::string& name, std::shared_ptr<Mesh> mesh) {
        meshes[name] = mesh;
        return *meshes[name];
    }

    static std::shared_ptr<Mesh> GetMesh(const std::string& name) {
        return meshes.at(name);
    }

    static void ClearMeshes() {
        meshes.clear(); 
    }

private:
    static inline std::unordered_map<std::string, std::shared_ptr<Shader>> shaders;
    static inline std::unordered_map<std::string, std::shared_ptr<Mesh>> meshes;
};