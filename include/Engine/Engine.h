#pragma once

#include <Engine/Core/Window.h>
#include <Engine/Core/Input.h>
#include <Engine/Core/AssetManager.h>
#include <Engine/Physics/PhysicsSystem.h>
#include <Engine/Renderer/Renderer.h>
#include <Engine/Scene/SceneManager.h>

class Engine {

public:
    Engine();
    ~Engine();
    bool Create(const char* title, int w, int h);
    //void SetApp(Application app){this->app = app;}
    void OnEvent(const SDL_Event& event);
    void OnUpdate(float dt);
    void Render();
    void Run();
    Window& getWindow(){return window;}
    Input& getInput(){return input;}
    Renderer& getRenderer(){return renderer;}
    PhysicsSystem& getPhysicsSystem(){return physics;}
    SceneManager* GetSceneManager();

private:
    Window window;
    Input input;
    PhysicsSystem physics;
    Renderer renderer;
    std::shared_ptr<SceneManager> sceneManager;
    //Scene& scene;
    //std::unique_ptr<SceneManager> sceneManager;
    //Application app;

};