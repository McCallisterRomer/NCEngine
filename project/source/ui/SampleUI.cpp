#include "SampleUI.h"
#include "Window.h"
#include "Input.h"
#include "config/Version.h"
#include "UIStyle.h"
#include "imgui/imgui.h"

#include "scenes/MenuScene.h"
#include "scenes/DemoScene.h"
#include "scenes/SpawnTest.h"

using namespace nc;

namespace
{
    constexpr auto PanelHeight = 200u;
    constexpr auto WindowFlags = ImGuiWindowFlags_NoCollapse |
                                 ImGuiWindowFlags_NoTitleBar |
                                 ImGuiWindowFlags_NoResize;
    
    void Spacing(unsigned count)
    {
        while(count--)
            ImGui::Spacing();
    }
}

namespace project::ui
{
    SampleUI::SampleUI(log::GameLog* gameLog, std::function<void()> widgetCallback)
        : m_gameLog{ gameLog },
          m_widgetCallback{ widgetCallback },
          m_windowDimensions{ window::GetDimensions() },
          m_isHovered{ false }
    {
        SetImGuiStyle();
        window::RegisterOnResizeReceiver(this);
    }

    SampleUI::~SampleUI()
    {
        window::UnregisterOnResizeReceiver(this);
    }

    void SampleUI::Draw()
    {
        CheckInput();

        ImGui::SetNextWindowPos({0, m_windowDimensions.y - PanelHeight});
        ImGui::SetNextWindowSize({m_windowDimensions.x, PanelHeight});

        if(ImGui::Begin("SampleUI", nullptr, WindowFlags))
        {
            auto columnCount = m_gameLog ? 3 : 2;
            ImGui::Columns(columnCount);

            if(m_widgetCallback)
                m_widgetCallback();
            else
                DrawDefaultWidget();

            if(m_gameLog)
            {
                ImGui::NextColumn();
                DrawLog();
            }

            ImGui::NextColumn();
            DrawSceneList();
        } ImGui::End();

        m_isHovered = ImGui::IsAnyWindowHovered();
    }

    void SampleUI::CheckInput()
    {
        using namespace nc::input;
        if(GetKeyDown(KeyCode::One))
            scene::Change(std::make_unique<MenuScene>());
        else if(GetKeyDown(KeyCode::Two))
            scene::Change(std::make_unique<DemoScene>());
        else if(GetKeyDown(KeyCode::Three))
            scene::Change(std::make_unique<SpawnTest>());
    }

    void SampleUI::DrawDefaultWidget()
    {
        if(ImGui::BeginChild("DefaultWidget", {0,0}, true))
        {
            ImGui::Text("NcEngine Samples");
            ImGui::Text("version");
            ImGui::SameLine();
            ImGui::Text(NC_PROJECT_VERSION);
            Spacing(8);
            ImGui::Text("Press \"~\" to open the editor.");
            Spacing(8);
            ImGui::Text("Provide a callback to draw here.");
        } ImGui::EndChild();
    }

    void SampleUI::DrawLog()
    {
        ImGui::Text("Log");
        if(ImGui::BeginChild("LogPanel", {0,0}, true))
        {
            for(auto& item : m_gameLog->GetItems())
            {
                ImGui::Text(item.c_str());
            }
        } ImGui::EndChild();
    }

    void SampleUI::DrawSceneList()
    {
        ImGui::Text("Scenes");
        if(ImGui::BeginChild("SceneList", {0,0}, true))
        {
            static bool selected = false;
            if(ImGui::Selectable("1. Worms", &selected))
                scene::Change(std::make_unique<MenuScene>());

            if(ImGui::Selectable("2. Assorted Rendering", &selected))
                scene::Change(std::make_unique<DemoScene>());

            if(ImGui::Selectable("3. Spawn Test", &selected))
                scene::Change(std::make_unique<SpawnTest>());

            if(ImGui::Selectable("4. Collision Test", &selected))
            {
            }
            if(ImGui::Selectable("5. Jare Scratch", &selected))
            {
            }
            if(ImGui::Selectable("6. Cal Scratch", &selected))
            {
            }
        } ImGui::EndChild();
    }

    bool SampleUI::IsHovered()
    {
        return m_isHovered;
    }

    void SampleUI::OnResize(nc::Vector2 dimensions)
    {
        m_windowDimensions = dimensions;
    }
} //end namespace project::ui
