#include "Engine.h"
#include "NCE.h"
#include "NCException.h"
#include "ProjectSettings.h"
#include "Window.h"
#include "ComponentManager.h"
#include "SceneManager.h"
#include "RenderingSystem.h"
#include "CollisionSystem.h"
#include "HandleManager.h"
#include "Camera.h"
#include "Renderer.h"

#include <iostream>

namespace nc::engine
{

struct EntityMaps
{
    std::unordered_map<EntityHandle, Entity> AwaitingInitialize;
    std::unordered_map<EntityHandle, Entity> Active;
    std::unordered_map<EntityHandle, Entity> AwaitingDestroy;
};


Engine::Engine()
{
    auto wndDim = Window::Instance->GetWindowDimensions();
    m_entities = std::make_unique<EntityMaps>();
    m_subsystem.Rendering = std::make_unique<RenderingSystem>(wndDim.first, wndDim.second, Window::Instance->GetHWND());
    m_subsystem.Collision = std::make_unique<CollisionSystem>();
    //m_subsystem.Transform = std::make_unique<TransformSystem>();
    m_subsystem.TransformSystem = std::make_unique<ComponentManager<Transform>>();
    m_subsystem.Handle = std::make_unique<HandleManager<EntityHandle>>();
}

Engine::~Engine() {}

bool Engine::DoesEntityExist(EntityHandle handle) { return (m_entities->Active.count(handle) > 0) || (m_entities->AwaitingInitialize.count(handle) > 0); }


auto& Engine::GetMapContainingEntity(EntityHandle handle, bool checkAll) noexcept(false)
{
    if (m_entities->Active.count(handle) > 0)
        return m_entities->Active;
    else if (m_entities->AwaitingInitialize.count(handle) > 0)
        return m_entities->AwaitingInitialize;

    if (checkAll && (m_entities->AwaitingDestroy.count(handle) > 0) ) //only check AwaitingDestroy if checkAll flag is set
        return m_entities->AwaitingDestroy;

    throw DefaultException("EntityNotFoundException");
}

Entity* Engine::GetEntityPtrFromAnyMap(EntityHandle handle) noexcept(false)
{
    return &GetMapContainingEntity(handle, true).at(handle);
}

void Engine::MainLoop()
{
    NCE nce(this);
    time::Time ncTime;
    scene::SceneManager sceneManager;

    m_mainCameraView = CreateEntity(Vector3(0.0f, 0.0f, -15.0f), Vector3::Zero(), Vector3::Zero(), "MainCamera");
    m_mainCameraView.Entity()->AddComponent<Camera>();

    while(m_engineState.isRunning)
    {
        /* CYCLE START */
        ncTime.UpdateTime();
        Window::Instance->ProcessSystemMessages();

        /* PHYSICS */
        /** @note Change this so physics 'simulates' running at a fixed interval.
         * It may need to run multiple times in a row in cases where FrameUpdate()
         * runs slowly and execution doesn't return back to physics in time for the 
         * next interval.
         */
        if (time::Time::FixedDeltaTime > ProjectSettings::displaySettings.fixedUpdateInterval)
        {
            FixedUpdate();
            ncTime.ResetFixedDeltaTime();
        }

        /* FRAME */
        // if (time::Time::FrameDeltaTime > ProjectSettings::displaySettings.frameUpdateInterval)
        // {
        //     FrameUpdate();
        //     input::Flush();
        //     ncTime.ResetFrameDeltaTime();
        // }
        FrameUpdate();
        input::Flush();
        ncTime.ResetFrameDeltaTime();

        /* CYCLE CLEANUP */

    } //end main loop
}

void Engine::FrameUpdate()
{
    // user component init and logic
    SendOnInitialize();
    SendFrameUpdate();

    // rendering
    m_subsystem.Rendering->StartRenderCycle(m_subsystem.TransformSystem->GetVector());

    // cleanup
    SendOnDestroy();
}

void Engine::FixedUpdate()
{
    // user component fixed tick logic
    SendFixedUpdate();

    // check collisions
    m_subsystem.Collision->CheckCollisions(m_subsystem.TransformSystem->GetVector());
}

void Engine::Exit()
{
    m_engineState.isRunning = false;
}

EntityView Engine::CreateEntity(Vector3 pos, Vector3 rot, Vector3 scale, const std::string& tag)
{
    EntityHandle newHandle = m_subsystem.Handle->GenerateNewHandle();
    Entity newEntity = Entity(newHandle, tag);

    ComponentHandle transformHandle = m_subsystem.TransformSystem->GetCurrentHandle() + 1;

    EntityView view(newHandle, transformHandle);

    newEntity.TransformHandle = m_subsystem.TransformSystem->Add(view);
    Transform* transformPtr = GetTransformPtr(newEntity.TransformHandle);
    transformPtr->Set(pos, rot, scale);
    m_entities->AwaitingInitialize.emplace(newHandle, newEntity);
    return EntityView(newHandle, newEntity.TransformHandle);
}

bool Engine::DestroyEntity(EntityHandle handle)
{
    if (!DoesEntityExist(handle))
        return false;
    auto& containingMap = GetMapContainingEntity(handle);
    m_entities->AwaitingDestroy.emplace(handle, containingMap.at(handle));
    containingMap.erase(handle);
    return true;
}

Entity* Engine::GetEntity(EntityHandle handle)
{
    if (!DoesEntityExist(handle))
        return nullptr;

    auto& containingMap = GetMapContainingEntity(handle);
    return &containingMap.at(handle);       
} 

Entity* Engine::GetEntity(const std::string& tag)
{
    for(auto& pair : m_entities->Active)
    {
        if(tag == pair.second.Tag)
        {
            return &pair.second;
        }
    }
    return nullptr;
}

Renderer* Engine::AddRenderer(EntityHandle handle)
{
    if(GetRenderer(handle))
    {
        return nullptr;
    }

    EntityView view(handle, GetEntity(handle)->TransformHandle);
    GetEntity(handle)->RendererHandle = m_subsystem.Rendering->Add(view);
    return GetRenderer(handle);
}

Renderer* Engine::GetRenderer(EntityHandle handle)
{
    return m_subsystem.Rendering->GetPointerTo(GetEntity(handle)->RendererHandle);
}

bool Engine::RemoveRenderer(EntityHandle handle)
{
    return m_subsystem.Rendering->Remove(handle);
}

nc::graphics::Graphics& Engine::GetGraphics()
{
    return m_subsystem.Rendering->GetGraphics();
}

EntityView* Engine::GetMainCamera()
{
    return &m_mainCameraView;
}

void Engine::BindEditorManager(utils::editor::EditorManager* editorManager)
{
    m_subsystem.Rendering->BindEditorManager(editorManager);
}

Transform* Engine::GetTransformPtr(ComponentHandle handle) { return m_subsystem.TransformSystem->GetPointerTo(handle); }

void Engine::SendOnInitialize() noexcept
{
    for(auto& pair : m_entities->AwaitingInitialize)
    {
        pair.second.SendOnInitialize();
        m_entities->Active.emplace(std::move(pair));
    }
    m_entities->AwaitingInitialize.clear();
}

void Engine::SendFrameUpdate() noexcept
{
    for(auto& pair : m_entities->Active)
    {
        pair.second.SendFrameUpdate();
    }
}

void Engine::SendFixedUpdate() noexcept
{
    for(auto& pair : m_entities->Active)
    {
        pair.second.SendFixedUpdate();
    }
}

void Engine::SendOnDestroy() noexcept
{
    for(auto& pair : m_entities->AwaitingDestroy)
    {
        Entity* entityPtr = GetEntityPtrFromAnyMap(pair.second.Handle);
        if (entityPtr == nullptr)
        {
            //std::cout << "Engine::SendOnDestroy - entityPtr is null\n";
            continue;
        }

        pair.second.SendOnDestroy();
        m_subsystem.TransformSystem->Remove(entityPtr->TransformHandle);
    }
    m_entities->AwaitingDestroy.clear();
}
}// end namespace nc::internal