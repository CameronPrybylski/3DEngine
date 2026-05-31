#include <Engine/Scene/SceneManager.h>


SceneManager::~SceneManager()
{
    scenes.clear();
}

void SceneManager::AddScene(std::string sceneName, std::shared_ptr<Scene> scene)
{
    scenes[sceneName] = scene;
}

void SceneManager::SwitchTo(std::string sceneName)
{
    if(scenes.find(sceneName) != scenes.end())
    {
        currentScene = scenes[sceneName].get();
    }
}

Scene* SceneManager::GetCurrentScene()
{
    return currentScene;
}

bool SceneManager::CheckEndScene()
{
    return currentScene->CheckEndScene();
}

void SceneManager::ChangeScene()
{
    std::string nextScene = currentScene->GetNextScene();
    currentScene->SetEndScene(false);
    SwitchTo(nextScene);
    currentScene->Init();
}