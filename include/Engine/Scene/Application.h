#pragma once

#include <Engine/Engine.h>

class Application {
public:
    Application(){}

    bool Create(const char* title, int w, int h);

    void Run();

    Engine& GetEngine(){return engine;}

    void AddScene(std::string sceneName, std::shared_ptr<Scene> scene);
    void SetScene(std::string sceneName);

    float GetScreenWidth()  const {return screenWidth;}
    float GetScreenHeight() const {return screenHeigt;}

private:
    //std::shared_ptr<SceneManager> sceneManager;
    Engine engine;
    float screenWidth;
    float screenHeigt;
};