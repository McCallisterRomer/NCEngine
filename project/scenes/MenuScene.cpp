#include "MenuScene.h"
#include "Ecs.h"
#include "MainCamera.h"
#include "UI.h"
#include "config/ProjectConfig.h"
#include "components/DebugComponents.h"
#include "project/components/CubeRotator.h"
#include "project/components/MouseFollower.h"
#include "source/Prefabs.h"
#include "graphics/materials/Material.h"

#include <cstdlib>
#include <ctime>

using namespace nc;

namespace project
{
    void MenuScene::Load()
    {
        project::config::ProjectConfig projectConfig;
        projectConfig.Load();

        m_ui = std::make_unique<project::ui::MainMenuUI>(projectConfig);
        nc::ui::UI::Set(m_ui.get());
        auto materialProperties = graphics::MaterialProperties{};

        prefab::InitializeResources();

        // Light
        auto lvHandle = Ecs::CreateEntity(Vector3::Zero(), Quaternion::Identity(), Vector3::One(), "Point Light");
        auto pointLight = Ecs::AddComponent<PointLight>(lvHandle);
        pointLight->Set(pointLight->PixelConstBufData.pos, 0.5f, {0.443f, 0.412f, 0.412f}, {0.4751f, 0.525f, 1.0f}, 3.56f, 0.00f, 0.05f, 0.00f);
        Ecs::AddComponent<project::MouseFollower>(lvHandle);

        // CamController
        auto camHandle = Ecs::CreateEntity("Main Camera");
        auto camComponentPtr = Ecs::AddComponent<Camera>(camHandle);
        camera::MainCamera::Set(camComponentPtr);
        
        // Debug Controller
        auto debugHandle = Ecs::CreateEntity("Debug Controller");
        Ecs::AddComponent<SceneReset>(debugHandle);
        Ecs::AddComponent<Timer>(debugHandle);

        const std::vector<std::string> ncTextures = std::vector<std::string>({"project//Textures//Logo//Logo3d_Material_BaseColor.png", "project//Textures//Logo//Logo3d_Material_Normal.png", "project//Textures//Logo//Logo3d_Material_Roughness.png", "nc//source//graphics//DefaultTexture.png"});
        graphics::Material ncMaterial =graphics::Material::CreateMaterial<graphics::TechniqueType::PhongShadingTechnique>(ncTextures, materialProperties);
        auto ncMesh = graphics::Mesh{"project//Models//Logo3d.fbx"};
        std::srand(std::time(0));
        int posRange = 30;
        int rotRange = 90;
        for(unsigned i = 0; i < 40; ++i)
        {
            auto xPos = (float)(rand() % posRange) - (posRange / 2);
            auto yPos = (float)(rand() % posRange) - (posRange / 2);
            auto zPos = (float)(rand() % posRange) + (posRange / 2);
            auto xRot = (float)(rand() % rotRange);
            auto yRot = (float)(rand() % rotRange);
            auto zRot = (float)(rand() % rotRange);
            auto ncHandle = Ecs::CreateEntity({xPos, yPos, zPos}, Quaternion::FromEulerAngles(xRot, yRot, zRot), {0.75f, 0.75f, 0.75f}, "nc");
            Ecs::AddComponent<Renderer>(ncHandle, ncMesh, ncMaterial);
            Ecs::AddComponent<project::CubeRotator>(ncHandle);
        }
    }

    void MenuScene::Unload()
    {
        nc::ui::UI::Set(nullptr);
        m_ui = nullptr;
    }
} // end namespace project