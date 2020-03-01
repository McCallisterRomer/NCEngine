#pragma once
#include "NCWinDef.h"

namespace nc::graphics::internal { class Graphics; }

namespace nc::editor
{
    class EditorManager
    {
        public:
            EditorManager(HWND hwnd, nc::graphics::internal::Graphics& graphics);
            ~EditorManager() noexcept;

            LRESULT WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);

            void BeginFrame();
            void EndFrame();

            void ToggleGui() noexcept;
            void EnableGui() noexcept;
            void DisableGui() noexcept;

            bool IsGuiActive() const noexcept;

            static void SpeedControl(float* speed);

            static void CameraControl(float* zPos, float* phi, float* theta, float* xRot, float* yRot, float* zRot);

            static void PointLightControl(float* xPos,      float* yPos,      float* zPos,
                                          float* matColorR, float* matColorG, float* matColorB,
                                          float* ambientR,  float* ambientG,  float* ambientB,
                                          float* difColorR, float* difColorG, float* difColorB,
                                          float* difIntens, float* attConst,  float* attLin, float* attQuad);

        private:
            bool m_isGuiActive;
    };
}