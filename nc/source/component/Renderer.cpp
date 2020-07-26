#include "Renderer.h"
#include "graphics/Graphics.h"
#include "graphics/Model.h"
#include "graphics/d3dresource/GraphicsResource.h"
#include "NcCommon.h"

#ifdef NC_EDITOR_ENABLED
#include "imgui/imgui.h"
#include "utils/editor/EditorManager.h"
#endif

namespace nc
{
    Renderer::Renderer()
        : m_model{ nullptr },
          m_transform{ nullptr }
    {
    }
    
    Renderer::Renderer(graphics::Mesh& mesh, graphics::PBRMaterial& material)
        : m_model{ std::make_unique<graphics::Model>(mesh, material) },
          m_transform{ nullptr }
    {
    }

    Renderer::Renderer(Renderer&& other)
    {
        m_handle = other.GetHandle();
        m_parentHandle = other.GetParentHandle();
        m_model = std::move(other.m_model);
    }

    Renderer& Renderer::operator=(Renderer&& other)
    {
        m_handle = other.GetHandle();
        m_parentHandle = other.GetParentHandle();
        m_model = std::move(other.m_model);
        return *this;
    }

    #ifdef NC_EDITOR_ENABLED
    // void Renderer::EditorGuiElement()
    // {
    //     std::string str = std::to_string(GetHandle());

    //     auto mat = m_model->GetMaterial();

    //     ImGui::PushItemWidth(40.0f);
    //         ImGui::Spacing();
    //         ImGui::Separator();
    //             ImGui::Text("Renderer");
    //             ImGui::Indent();
    //                 ImGui::Text("ID: ");  ImGui::SameLine();    ImGui::Text(str.c_str());
    //                 ImGui::Text("Material Color");  ImGui::SameLine();  bool mcDirty = ImGui::ColorEdit3("##mc", &(mat->color.x), ImGuiColorEditFlags_NoInputs);
    //                 ImGui::Text("Specular");
    //                 ImGui::Indent();
    //                 ImGui::Text("Intensity");  ImGui::SameLine();  bool siDirty = ImGui::DragFloat("##si",  &(mat->specularIntensity), 0.75f, 0.05f,   4.0f, "%.2f", 2);
    //                 ImGui::Text("Power    ");  ImGui::SameLine();  bool spDirty = ImGui::DragFloat("##sp",  &(mat->specularPower),     0.75f,  1.0f, 200.0f, "%.2f", 2);
    //                 ImGui::Unindent();
    //             ImGui::Unindent();
    //         ImGui::Separator();
    //     ImGui::PopItemWidth();

    //     if(mcDirty || siDirty || spDirty)
    //     {
    //         SyncMaterialData();
    //     }
    // }

    // void Renderer::SyncMaterialData()
    // {
    //     if(!m_model) return;

    //     using namespace nc::graphics;
    //     auto pConstPS = m_model->QueryGraphicsResource<d3dresource::PixelConstBuffer<Material>>();
	//     assert(pConstPS != nullptr);
	//     pConstPS->Update(*m_model->GetMaterial());
    // }
    
    #endif

    void Renderer::Update(graphics::Graphics * gfx)
    {
        if (!m_transform)
        {
            m_transform = NcGetEngineComponent<Transform>(m_parentHandle);
        }

        if (!m_transform)
        {
            throw std::runtime_error("Renderer::Update - bad trans ptr");
        }

        m_model->UpdateTransformationMatrix(m_transform);
        m_model->Draw(gfx);
    }

    void Renderer::SetMesh(graphics::Mesh& mesh)
    {
        m_model->SetMesh(mesh);
    }
    
    void Renderer::SetMaterial(graphics::PBRMaterial& material) 
    {
        m_model->SetMaterial(material);
    }

}