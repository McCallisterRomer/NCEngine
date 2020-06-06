#include "Renderer.h"
#include "graphics/Graphics.h"
#include "graphics/Model.h"
#include "NCE.h"
#include "graphics/d3dresource/GraphicsResource.h"

#ifdef NC_DEBUG
#include "utils/editor/imgui/imgui.h"
#include "utils/editor/EditorManager.h"
#endif

namespace nc
{
    Renderer::Renderer()
    {}

    Renderer::Renderer(Renderer&& other)
    {
        m_handle = other.GetHandle();
        m_parentView = *other.GetParentView();
        m_model = std::move(other.m_model);
    }

    Renderer& Renderer::operator=(Renderer&& other)
    {
        m_handle = other.GetHandle();
        m_parentView = *other.GetParentView();
        m_model = std::move(other.m_model);
        return *this;
    }

    #ifdef NC_DEBUG
    void Renderer::EditorGuiElement()
    {
        std::string str = std::to_string(GetHandle());

        auto mat = m_model->GetMaterial();

        ImGui::PushItemWidth(40.0f);
            ImGui::Spacing();
            ImGui::Separator();
                ImGui::Text("Renderer");
                ImGui::Indent();
                    ImGui::Text("ID: ");  ImGui::SameLine();    ImGui::Text(str.c_str());
                    ImGui::Text("Material Color");  ImGui::SameLine();  bool mcDirty = ImGui::ColorEdit3("##mc", &(mat->color.x), ImGuiColorEditFlags_NoInputs);
                    ImGui::Text("Specular");
                    ImGui::Indent();
                    ImGui::Text("Intensity");  ImGui::SameLine();  bool siDirty = ImGui::DragFloat("##si",  &(mat->specularIntensity), 0.75f, 0.05f,   4.0f, "%.2f", 2);
                    ImGui::Text("Power    ");  ImGui::SameLine();  bool spDirty = ImGui::DragFloat("##sp",  &(mat->specularPower),     0.75f,  1.0f, 200.0f, "%.2f", 2);
                    ImGui::Unindent();
                ImGui::Unindent();
            ImGui::Separator();
        ImGui::PopItemWidth();

        if(mcDirty || siDirty || spDirty)
        {
            SyncMaterialData();
        }
    }

    void Renderer::SyncMaterialData()
    {
        if(!m_model) return;

        using namespace nc::graphics;
        auto pConstPS = m_model->QueryGraphicsResource<d3dresource::PixelConstantBuffer<Material>>();
	    assert(pConstPS != nullptr);
	    pConstPS->Update(NCE::GetGraphics(), *m_model->GetMaterial());
    }
    #endif

    void Renderer::Update(graphics::Graphics * graphics)
    {
        m_model->UpdateTransformationMatrix(NCE::GetTransform(*GetParentView()));
        m_model->Draw(graphics);
    }

    void Renderer::SetModel(graphics::Graphics * graphics, graphics::Mesh& mesh, DirectX::XMFLOAT3& materialColor)
    {
        m_model = std::make_unique<graphics::Model>(graphics, mesh, materialColor);
    }
    

}