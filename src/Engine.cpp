#include <Engine/Engine.h>
#include <iostream>


Engine::Engine()
{
    sceneManager = std::make_shared<SceneManager>();
}

Engine::~Engine()
{
    AssetManager::ClearShaders();
    AssetManager::ClearMeshes();
}

bool Engine::Create(const char* title, int w, int h)
{
    if(!window.Init(title, w, h))
    {
        return false;
    }
    
    return true;
}

void Engine::OnEvent(const SDL_Event& event)
{
    if(event.type != SDL_TEXTINPUT)
    {
        input.OnEvent(event);
        sceneManager->GetCurrentScene()->OnEvent(input);
    }
}

void Engine::OnUpdate(float dt)
{
    sceneManager->GetCurrentScene()->OnUpdate(input, physics, dt);
}

void Engine::Render()
{
    renderer.Clear();
    if(sceneManager->CheckEndScene())
    {
        sceneManager->ChangeScene();
        physics.ClearBodies();
        sceneManager->GetCurrentScene()->LoadPhysics(physics);
    }
    sceneManager->GetCurrentScene()->DrawObjects(renderer);
}

SceneManager *Engine::GetSceneManager()
{
    return sceneManager.get();
}


void Engine::Run()
{
    SDL_GL_SetSwapInterval(1); 
    Uint32 previousTime = SDL_GetTicks();
    
    const Uint32 FRAME_DELAY = 1000 / 60; // ~16.67 ms per frame
    Uint32 frameStart;
    int frameTime;

    while(!input.ShutDown())
    {
        frameStart = SDL_GetTicks();
        Uint32 currentTime = SDL_GetTicks();
        float dt = (currentTime - previousTime) / 1000.0f; // milliseconds to seconds
        previousTime = currentTime;
        
        SDL_Event event;
        while(window.PollEvent(event))
        {
            OnEvent(event);
        }

       if (dt > 0.2f)
       {
            dt = 0.016f; // clamp extremely bad delta times
       }

        OnUpdate(dt);
        Render();
        
        window.Update();

        // Calculate how long this frame took
        frameTime = SDL_GetTicks() - frameStart;

        // If frame finished early, delay to cap FPS
        if (frameTime < FRAME_DELAY)
        {
            SDL_Delay(FRAME_DELAY - frameTime);
        }
    }
}

