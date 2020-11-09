#include "EngineImpl.h"

#include "camera/MainCamera.h"
#include "config/Config.h"
#include "graphics/Graphics.h"
#include "input/Input.h"
#include "ecs/ECS.h"
#include "ecs/RenderingSystem.h"
#include "ecs/LightSystem.h"
#include "ecs/TransformSystem.h"
#include "NcDebug.h"
#include "physics/PhysicsSystem.h"
#include "scene/SceneManager.h"
#include "scenes/InitialScene.h"
#include "time/NcTime.h"
#include "ui/UISystem.h"
#include "window/Window.h"

#include <iostream>

namespace nc::engine
{
EngineImpl::EngineImpl(HINSTANCE hInstance, Engine* topLevelEngine)
{
    isRunning = false;
    m_config.Load();
    m_frameDeltaTimeFactor = 1.0f;
    m_logger = std::make_unique<log::Logger>(m_config.project.logFilePath);
    m_window = std::make_unique<Window>(hInstance, topLevelEngine, m_config);
    m_transform = std::make_unique<ecs::TransformSystem>();
    auto dim = m_window->GetWindowDimensions();
    auto hwnd = m_window->GetHWND();
    m_rendering = std::make_unique<ecs::RenderingSystem>
    (
        hwnd, dim.X(), dim.Y(),
        m_config.graphics.nearClip,
        m_config.graphics.farClip,
        m_config.graphics.launchInFullscreen
    );
    m_light = std::make_unique<ecs::LightSystem>();
    m_physics = std::make_unique<physics::PhysicsSystem>();
    m_ecs = std::make_unique<ecs::ECS>(m_light.get(), m_rendering.get(), m_transform.get());
    m_uiSystem = std::make_unique<ui::UISystem>(hwnd, m_rendering->GetGraphics());
    m_sceneManager = std::make_unique<scene::SceneManager>(std::make_unique<InitialScene>());
    m_mainCamera = std::make_unique<camera::MainCamera>();
    #ifdef NC_EDITOR_ENABLED
    m_frameLogicTimer = std::make_unique<nc::time::Timer>();
    #endif

    m_window->BindGraphics(m_rendering->GetGraphics());
    m_window->BindUISystem(m_uiSystem.get());

    V_LOG("Engine initialized");
}

EngineImpl::~EngineImpl()
{
}

void EngineImpl::MainLoop()
{
    V_LOG("Starting engine loop");
    time::Time ncTime;
    m_sceneManager->LoadActiveScene();
    isRunning = true;

    while(isRunning)
    {
        if(input::GetKey(input::KeyCode::R))
        {
            m_rendering->GetGraphics()->ResizeTarget(500, 500);
        }

        if(input::GetKey(input::KeyCode::F))
        {
            m_rendering->GetGraphics()->ToggleFullscreen();
        }

        ncTime.UpdateTime();
        m_window->ProcessSystemMessages();

        /** @note Change this so physics 'simulates' running at a fixed interval.
         * It may need to run multiple times in a row in cases where FrameUpdate()
         * runs slowly and execution doesn't return back to physics in time for the 
         * next interval.
         */
        if (time::Time::FixedDeltaTime > m_config.physics.fixedUpdateInterval)
        {
            FixedUpdate();
            ncTime.ResetFixedDeltaTime();
        }

        auto dt = time::Time::FrameDeltaTime * m_frameDeltaTimeFactor;

        #ifdef NC_EDITOR_ENABLED
        m_frameLogicTimer->Start();
        #endif
        FrameLogic(dt);
        #ifdef NC_EDITOR_ENABLED
        m_frameLogicTimer->Stop();
        #endif
        FrameRender(dt);
        FrameCleanup();
        ncTime.ResetFrameDeltaTime();
    } //end main loop

    Shutdown();
}

void EngineImpl::Shutdown()
{
    V_LOG("Shutdown EngineImpl");
    m_config.Save();
    ClearECSState();
}

void EngineImpl::ClearECSState()
{
    V_LOG("Clearing engine state");
    auto handles = std::vector<EntityHandle>{};
    for(const auto& pair : m_ecs->GetActiveEntities())
    {
        handles.emplace_back(pair.first);
    }
    for(const auto handle : handles)
    {
        NcDestroyEntity(handle);
    }
    SendOnDestroyToEntities();
    
    m_ecs->ClearSystems();
    m_mainCamera->ClearTransform();
    m_rendering->Clear();
    m_light->Clear();
}

void EngineImpl::DoSceneSwap()
{
    V_LOG("Swapping scene");
    m_sceneManager->UnloadActiveScene();
    ClearECSState();
    m_sceneManager->DoSceneChange();
    m_sceneManager->LoadActiveScene();
}

void EngineImpl::FrameLogic(float dt)
{
    SendFrameUpdateToEntities(dt);
}

void EngineImpl::FrameRender(float dt)
{
    (void)dt;
    m_uiSystem->FrameBegin();
    m_rendering->FrameBegin();
    m_light->BindLights();
    m_rendering->Frame();
    m_uiSystem->Frame(&m_frameDeltaTimeFactor, m_frameLogicTimer->Value(), m_ecs->GetActiveEntities());
    m_uiSystem->FrameEnd();
    m_rendering->FrameEnd();
}

void EngineImpl::FixedUpdate()
{
    SendFixedUpdateToEntities();
}

void EngineImpl::FrameCleanup()
{
    SendOnDestroyToEntities();
    if(m_sceneManager->IsSceneChangeScheduled())
    {
        DoSceneSwap();
    }
    input::Flush();
}

void EngineImpl::SendFrameUpdateToEntities(float dt)
{
    for(auto & pair : m_ecs->GetActiveEntities())
    {
        pair.second.SendFrameUpdate(dt);
    }
}

void EngineImpl::SendFixedUpdateToEntities()
{
    for(auto & pair : m_ecs->GetActiveEntities())
    {
        pair.second.SendFixedUpdate();
    }
}

void EngineImpl::SendOnDestroyToEntities()
{
    auto & toDestroy = m_ecs->GetToDestroyEntities();
    for(auto & pair : toDestroy)
    {
        Entity* entityPtr = m_ecs->GetEntityPtrFromAnyMap(pair.second.Handle);
        if (entityPtr == nullptr)
        {
            continue;
        }

        pair.second.SendOnDestroy();
        const auto& handles = entityPtr->Handles;
        m_ecs->RemoveTransform(handles.transform);
        m_rendering->Remove(handles.renderer);
        m_light->Remove(handles.pointLight);
    }
    toDestroy.clear();
}

config::Config& EngineImpl::GetConfig()
{
    return m_config;
}
} // end namespace nc::engine