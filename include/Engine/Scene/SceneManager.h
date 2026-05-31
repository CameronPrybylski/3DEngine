#pragma once

#include<Engine/Scene/Scene.h>

class SceneManager{
public:
    ~SceneManager();
    void AddScene(std::string sceneName, std::shared_ptr<Scene> scene);
    Scene* GetCurrentScene();
    void SwitchTo(std::string sceneName);
    bool CheckEndScene();
    void ChangeScene();

private:
    std::unordered_map<std::string, std::shared_ptr<Scene>> scenes;
    Scene* currentScene;
};