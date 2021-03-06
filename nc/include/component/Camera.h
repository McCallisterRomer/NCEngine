#pragma once
#include "Component.h"

namespace nc
{
    class Camera : public Component
    {
        public:
            Camera(EntityHandle handle) noexcept;
            ~Camera() = default;
            Camera(const Camera&) = delete;
            Camera(Camera&&) = delete;
            Camera& operator=(const Camera&) = delete;
            Camera& operator=(Camera&&) = delete;

            #ifdef NC_EDITOR_ENABLED
            void EditorGuiElement() override;
            #endif
    };
}