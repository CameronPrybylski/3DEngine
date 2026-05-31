#pragma once

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <Engine/Renderer/Mesh.h>
#include <Engine/Renderer/BatchMesh.h>
#include <Engine/Renderer/Texture.h>
#include <Engine/Scene/Transform.h>
#include <Engine/Scene/Camera.h>
#include <Engine/Core/AssetManager.h>

class TextTexture;

class Renderer{

public:
    Renderer();
    ~Renderer();
    void DrawQuad(const Mesh& mesh, const Transform& modelMatrix, const Camera& camera, Shader& shader, glm::vec4 color = {0.0f, 0.0f, 0.0f, 0.0f});
    void DrawBatch(const Mesh& mesh, const Camera& camera, Shader& shader, glm::vec4 color = {0.0f, 0.0f, 0.0f, 0.0f});
    void DrawTexturedQuad(const Mesh& mesh, const Transform& modelMatrix, const Camera& camera, Shader& shader, Texture& texture, glm::vec4 color = {0.0f, 0.0f, 0.0f, 0.0f});
    void DrawTexturedBatch(const Mesh& mesh, const Camera& camera, Shader& shader, std::vector<Texture>& textures, glm::vec4 color = {0.0f, 0.0f, 0.0f, 0.0f});
    void Clear();

private:

};