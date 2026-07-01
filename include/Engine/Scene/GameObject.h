#pragma once
#include <Engine/Renderer/Renderer.h>
#include <Engine/Renderer/QuadMesh.h>
#include <Engine/Renderer/ObjectMesh.h>
#include <Engine/Renderer/Material.h>
#include <Engine/Scene/Transform.h>
#include <Engine/Core/Input.h>

class GameObject {

public:
    GameObject();
    ~GameObject();

    virtual void OnEvent(const Input& input);
    virtual void Update(float dt);
    virtual void Update(const Input& input, float dt);
    virtual void Render(Renderer& renderer, const Camera& camera);
    virtual void OnCollision(std::shared_ptr<GameObject> collidedObj, glm::vec2 collisionNormal, float dt) {}

    bool IsBatched(){return batched;}

    std::shared_ptr<Mesh> mesh;
    Texture texture;
    Transform transform;
    std::map<std::string, Material> materialMap;
    RigidBodyComponent rigidBody;
    std::string shaderName;
    glm::vec4 color;
    std::string name;
    std::string type = "";
    bool batched = false;
    float scaleMulti = 1.0f;

};