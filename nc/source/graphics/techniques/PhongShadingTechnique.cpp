#include "PhongShadingTechnique.h"
#include "TechniqueType.h"
#include "graphics/materials/MaterialProperties.h"
#include "graphics/d3dresource/GraphicsResourceManager.h"
#include "Engine.h"

using namespace nc::graphics::d3dresource;

namespace
{
    const auto PhongInputElementDesc = std::vector<D3D11_INPUT_ELEMENT_DESC>
    {
        { "Position", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0,  0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
        { "Normal", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 },
        { "TexCoord", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 24, D3D11_INPUT_PER_VERTEX_DATA, 0 },
        { "Tangent", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 32, D3D11_INPUT_PER_VERTEX_DATA, 0 },
        { "Bitangent", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 44, D3D11_INPUT_PER_VERTEX_DATA, 0 }
    };
    
    const std::string SAMPLER_TAG = "texture_sampler_resource";
    const std::string BLENDER_TAG = "texture_blender_resource";
}

namespace nc::graphics
{
    PhongShadingTechnique::PhongShadingTechnique(const std::vector<std::string>& texturePaths, MaterialProperties materialProperties)
    {
        auto defaultShaderPath = nc::engine::Engine::GetConfig().graphics.shadersPath;

        Step single(0);
        {
            // Add Textures
            uint32_t shaderIndex = 0;
            for (const auto& texturePathRef : texturePaths) 
            {
                single.AddGraphicsResource(d3dresource::GraphicsResourceManager::Acquire<d3dresource::Texture>(texturePathRef, shaderIndex++));
            }

            // Add vertex shader
            auto pvs = GraphicsResourceManager::Acquire<VertexShader>(defaultShaderPath + "pbrvertexshader.cso");
            auto pvsbc = static_cast<VertexShader&>(*pvs).GetBytecode();
            single.AddGraphicsResource(std::move(pvs));
            single.AddGraphicsResource(GraphicsResourceManager::Acquire<InputLayout>("pbrvertexshader", PhongInputElementDesc, pvsbc));

            // Add pixel shader
            single.AddGraphicsResource(GraphicsResourceManager::Acquire<d3dresource::PixelShader>(defaultShaderPath + "pbrpixelshader.cso"));
            single.AddGraphicsResource(GraphicsResourceManager::Acquire<d3dresource::Blender>(BLENDER_TAG));
            single.AddGraphicsResource(GraphicsResourceManager::Acquire<d3dresource::Sampler>(SAMPLER_TAG));
            single.AddGraphicsResource(PixelConstantBuffer<MaterialProperties>::AcquireUnique(materialProperties, 1u));
        }
        AddStep(std::move(single));
    }

    size_t PhongShadingTechnique::GetUID(TechniqueType type, const std::vector<std::string>& texturePaths) noexcept
    {
        auto hash = std::to_string((uint8_t)type);
        for (const auto& texturePathRef : texturePaths) 
        {
            hash += texturePathRef;
        }
        return std::hash<std::string>{}(hash);
    }

}