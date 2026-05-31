#include <Engine/Scene/Application.h>
/*
SceneManager* Application::GetSceneManager()
{
    return sceneManager.get();
}

*/
bool Application::Create(const char* title, int w, int h)
{
    screenWidth = (float)w;
    screenHeigt = (float)h;
    return engine.Create(title, w, h);
}

void Application::Run()
{
    engine.Run();
}

void Application::AddScene(std::string sceneName, std::shared_ptr<Scene> scene)
{
    engine.GetSceneManager()->AddScene(sceneName, scene);
}

void Application::SetScene(std::string sceneName)
{
    engine.GetSceneManager()->SwitchTo(sceneName);
    engine.GetSceneManager()->GetCurrentScene()->Init();
    engine.getPhysicsSystem().ClearBodies();
    engine.GetSceneManager()->GetCurrentScene()->LoadPhysics(engine.getPhysicsSystem());
}