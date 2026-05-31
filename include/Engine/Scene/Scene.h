#pragma once

#include <SDL.h>
#include <json.hpp>
#include <Engine/Core/Input.h>
#include <Engine/Physics/PhysicsSystem.h>
#include <Engine/Scene/GameObject.h>
#include <Engine/Scene/Camera.h>
#include <Engine/Renderer/Renderer.h>

class Scene {
public: 
    Scene(float screenWidth, float screenHeight) : screenHeight(screenHeight), screenWidth(screenWidth) {}

    virtual void Init() = 0;

    void AddObject(std::string nameOfObject, std::shared_ptr<GameObject> object);

    virtual void OnEvent(const Input& input);

    virtual void OnUpdate(const Input& input, PhysicsSystem& physics, float dt);

    virtual void DrawObjects(Renderer& renderer);

    virtual void EndScene(std::string nextScene);

    virtual bool CheckEndScene(){return endScene;}

    virtual void SetEndScene(bool endScene){this->endScene = endScene;}

    virtual std::string GetNextScene(){return nextScene;}

    virtual void LoadPhysics(PhysicsSystem& physics);

protected:
    bool endScene = false;
    float screenWidth;
    float screenHeight;
    float leftScreenEdge;
    float rightScreenEdge;
    float topScreenEdge;
    float bottomScreenEdge;
    std::string nextScene;
    std::vector<std::shared_ptr<GameObject>> objectList;
    std::unordered_map<std::string, std::shared_ptr<GameObject>> objectMap;
    std::vector<std::shared_ptr<GameObject>> dynamicObjects;
    std::vector<std::shared_ptr<GameObject>> staticObjects;
    std::unordered_map<std::string, std::shared_ptr<GameObject>> nonDrawnObjects;
    Camera camera;
};