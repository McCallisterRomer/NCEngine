#include "CollisionBenchmark.h"
#include "MainCamera.h"
#include "imgui/imgui.h"
#include "shared/FPSTracker.h"
#include "shared/spawner/Spawner.h"

namespace
{
    std::function<int()> GetObjectCountCallback = nullptr;
    std::function<float()> GetFPSCallback = nullptr;
    std::function<void(unsigned)> SpawnCallback = nullptr;
    std::function<void(unsigned)> DestroyCallback = nullptr;

    int SpawnCount = 25;
    int DestroyCount = 25;

    void Widget()
    {
        ImGui::Text("Collision Benchmark");
        if(ImGui::BeginChild("Widget", {0,0}, true))
        {
            ImGui::Text("Objects: %d", GetObjectCountCallback());
            ImGui::Text("FPS: %.1f", GetFPSCallback());
            ImGui::Spacing(); ImGui::Spacing(); ImGui::Spacing();

            ImGui::SetNextItemWidth(100);
            ImGui::InputInt("##spawncount", &SpawnCount);
            SpawnCount = nc::math::Clamp(SpawnCount, 1, 30000);
            if(ImGui::Button("Spawn", {100, 20}))
                SpawnCallback(SpawnCount);
            ImGui::Spacing(); ImGui::Spacing(); ImGui::Spacing();

            ImGui::SetNextItemWidth(100);
            ImGui::InputInt("##destroycount", &DestroyCount);
            DestroyCount = nc::math::Clamp(DestroyCount, 1, 30000);
            if(ImGui::Button("Destroy", {100, 20}))
                DestroyCallback(DestroyCount);
        } ImGui::EndChild();
    }
}

namespace nc::sample
{
    void CollisionBenchmark::Load()
    {
        m_sceneHelper.Setup(false, true, Widget);

        auto camera = AddComponent<Camera>(CreateEntity({.tag = "Main Camera"}));
        camera::SetMainCamera(camera);

        SpawnBehavior spawnBehavior
        {
            .positionOffset = Vector3{0.0f, 0.0f, 35.0f},
            .positionRandomRange = Vector3::Splat(15.0f),
            .rotationRandomRange = Vector3::Splat(math::Pi / 2.0f)
        };

        auto spawnExtension = [](EntityHandle handle)
        {
            AddComponent<Collider>(handle, Vector3::One());
        };
        
        auto handle = CreateEntity({.tag = "Spawner"});
        auto spawner = AddComponent<Spawner>(handle, prefab::Resource::Cube, spawnBehavior, spawnExtension);
        GetObjectCountCallback = std::bind(Spawner::GetObjectCount, spawner);
        SpawnCallback = std::bind(Spawner::Spawn, spawner, std::placeholders::_1);
        DestroyCallback = std::bind(Spawner::Destroy, spawner, std::placeholders::_1);

        auto fpsTracker = AddComponent<FPSTracker>(handle);
        GetFPSCallback = std::bind(FPSTracker::GetFPS, fpsTracker);
    }

    void CollisionBenchmark::Unload()
    {
        GetObjectCountCallback = nullptr;
        GetFPSCallback = nullptr;
        SpawnCallback = nullptr;
        DestroyCallback = nullptr;
        m_sceneHelper.TearDown();
    }
}