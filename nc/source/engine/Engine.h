#pragma once

#include "ecs/EntityComponentSystem.h"
#include "graphics/rendergraph/FrameManager.h"
#include "graphics/Graphics.h"
#include "physics/PhysicsSystem.h"
#include "component/PointLightManager.h"
#include "scene/SceneSystem.h"
#include "ui/UIImpl.h"
#include "window/WindowImpl.h"

#include <functional>

namespace nc::core
{
    class Engine
    {
        public:
            Engine(HINSTANCE hInstance);
            ~Engine();
            void DisableRunningFlag();
            void MainLoop(std::unique_ptr<scene::Scene> initialScene);
            void Shutdown();
            void ClearState();
            void DoSceneSwap();
            void FrameLogic(float dt);
            void FrameRender();
            void FrameCleanup();

        private:
            bool m_isRunning;
            float m_frameDeltaTimeFactor;
            window::WindowImpl m_window;
            graphics::Graphics m_graphics;
            physics::PhysicsSystem m_physics;
            ecs::EntityComponentSystem m_ecs;
            ui::UIImpl m_ui;
            PointLightManager m_pointLightManager;
            scene::SceneSystem m_sceneSystem;
            graphics::FrameManager m_frameManager;

            void SetBindings();
    };
} // end namespace nc::engine