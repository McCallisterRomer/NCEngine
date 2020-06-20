//--------------------------------------------------------------------------------------
// File: ModelLoadSDKMESH.cpp
//
// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
//
// http://go.microsoft.com/fwlink/?LinkId=248929
//--------------------------------------------------------------------------------------

#include "pch.h"
#include "external/directx/tk/Model.h"
#include "external/directx/tk/DirectXHelpers.h"
#include "external/directx/tk/Effects.h"
#include "external/directx/tk/VertexTypes.h"
#include "BinaryReader.h"
#include "PlatformHelpers.h"
#include "SDKMesh.h"

using namespace DirectX;
using Microsoft::WRL::ComPtr;

namespace
{
    enum : unsigned int
    {
        PER_VERTEX_COLOR        = 0x1,
        SKINNING                = 0x2,
        DUAL_TEXTURE            = 0x4,
        NORMAL_MAPS             = 0x8,
        BIASED_VERTEX_NORMALS   = 0x10,
        USES_OBSOLETE_DEC3N     = 0x20,
    };

    struct MaterialRecordSDKMESH
    {
        std::shared_ptr<IEffect> effect;
        bool alpha;

        MaterialRecordSDKMESH() noexcept : alpha(false) {}
    };

    inline XMFLOAT3 GetMaterialColor(float r, float g, float b, bool srgb)
    {
        if (srgb)
        {
            XMVECTOR v = XMVectorSet(r, g, b, 1.f);
            v = XMColorSRGBToRGB(v);

            XMFLOAT3 result;
            XMStoreFloat3(&result, v);
            return result;
        }
        else
        {
            return XMFLOAT3(r, g, b);
        }
    }

    void LoadMaterial(const DXUT::SDKMESH_MATERIAL& mh,
        unsigned int flags,
        IEffectFactory& fxFactory,
        MaterialRecordSDKMESH& m,
        bool srgb)
    {
        wchar_t matName[DXUT::MAX_MATERIAL_NAME] = {};
        MultiByteToWideChar(CP_UTF8, 0, mh.Name, -1, matName, DXUT::MAX_MATERIAL_NAME);

        wchar_t diffuseName[DXUT::MAX_TEXTURE_NAME] = {};
        MultiByteToWideChar(CP_UTF8, 0, mh.DiffuseTexture, -1, diffuseName, DXUT::MAX_TEXTURE_NAME);

        wchar_t specularName[DXUT::MAX_TEXTURE_NAME] = {};
        MultiByteToWideChar(CP_UTF8, 0, mh.SpecularTexture, -1, specularName, DXUT::MAX_TEXTURE_NAME);

        wchar_t normalName[DXUT::MAX_TEXTURE_NAME] = {};
        MultiByteToWideChar(CP_UTF8, 0, mh.NormalTexture, -1, normalName, DXUT::MAX_TEXTURE_NAME);

        if (flags & DUAL_TEXTURE && !mh.SpecularTexture[0])
        {
            DebugTrace("WARNING: Material '%s' has multiple texture coords but not multiple textures\n", mh.Name);
            flags &= ~static_cast<unsigned int>(DUAL_TEXTURE);
        }

        if (flags & NORMAL_MAPS)
        {
            if (!mh.NormalTexture[0])
            {
                flags &= ~static_cast<unsigned int>(NORMAL_MAPS);
                *normalName = 0;
            }
        }
        else if (mh.NormalTexture[0])
        {
            DebugTrace("WARNING: Material '%s' has a normal map, but vertex buffer is missing tangents\n", mh.Name);
            *normalName = 0;
        }

        EffectFactory::EffectInfo info;
        info.name = matName;
        info.perVertexColor = (flags & PER_VERTEX_COLOR) != 0;
        info.enableSkinning = (flags & SKINNING) != 0;
        info.enableDualTexture = (flags & DUAL_TEXTURE) != 0;
        info.enableNormalMaps = (flags & NORMAL_MAPS) != 0;
        info.biasedVertexNormals = (flags & BIASED_VERTEX_NORMALS) != 0;

        if (mh.Ambient.x == 0 && mh.Ambient.y == 0 && mh.Ambient.z == 0 && mh.Ambient.w == 0
            && mh.Diffuse.x == 0 && mh.Diffuse.y == 0 && mh.Diffuse.z == 0 && mh.Diffuse.w == 0)
        {
            // SDKMESH material color block is uninitalized; assume defaults
            info.diffuseColor = XMFLOAT3(1.f, 1.f, 1.f);
            info.alpha = 1.f;
        }
        else
        {
            info.ambientColor = GetMaterialColor(mh.Ambient.x, mh.Ambient.y, mh.Ambient.z, srgb);
            info.diffuseColor = GetMaterialColor(mh.Diffuse.x, mh.Diffuse.y, mh.Diffuse.z, srgb);
            info.emissiveColor = GetMaterialColor(mh.Emissive.x, mh.Emissive.y, mh.Emissive.z, srgb);

            if (mh.Diffuse.w != 1.f && mh.Diffuse.w != 0.f)
            {
                info.alpha = mh.Diffuse.w;
            }
            else
                info.alpha = 1.f;

            if (mh.Power > 0)
            {
                info.specularPower = mh.Power;
                info.specularColor = XMFLOAT3(mh.Specular.x, mh.Specular.y, mh.Specular.z);
            }
        }

        info.diffuseTexture = diffuseName;
        info.specularTexture = specularName;
        info.normalTexture = normalName;

        m.effect = fxFactory.CreateEffect(info, nullptr);
        m.alpha = (info.alpha < 1.f);
    }

    void LoadMaterial(const DXUT::SDKMESH_MATERIAL_V2& mh,
        unsigned int flags,
        IEffectFactory& fxFactory,
        MaterialRecordSDKMESH& m)
    {
        wchar_t matName[DXUT::MAX_MATERIAL_NAME] = {};
        MultiByteToWideChar(CP_UTF8, 0, mh.Name, -1, matName, DXUT::MAX_MATERIAL_NAME);

        wchar_t albetoTexture[DXUT::MAX_TEXTURE_NAME] = {};
        MultiByteToWideChar(CP_UTF8, 0, mh.AlbetoTexture, -1, albetoTexture, DXUT::MAX_TEXTURE_NAME);

        wchar_t normalName[DXUT::MAX_TEXTURE_NAME] = {};
        MultiByteToWideChar(CP_UTF8, 0, mh.NormalTexture, -1, normalName, DXUT::MAX_TEXTURE_NAME);

        wchar_t rmaName[DXUT::MAX_TEXTURE_NAME] = {};
        MultiByteToWideChar(CP_UTF8, 0, mh.RMATexture, -1, rmaName, DXUT::MAX_TEXTURE_NAME);

        wchar_t emissiveName[DXUT::MAX_TEXTURE_NAME] = {};
        MultiByteToWideChar(CP_UTF8, 0, mh.EmissiveTexture, -1, emissiveName, DXUT::MAX_TEXTURE_NAME);

        EffectFactory::EffectInfo info;
        info.name = matName;
        info.perVertexColor = false;
        info.enableSkinning = false;
        info.enableDualTexture = false;
        info.enableNormalMaps = true;
        info.biasedVertexNormals = (flags & BIASED_VERTEX_NORMALS) != 0;
        info.alpha = (mh.Alpha == 0.f) ? 1.f : mh.Alpha;

        info.diffuseTexture = albetoTexture;
        info.specularTexture = rmaName;
        info.normalTexture = normalName;
        info.emissiveTexture = emissiveName;

        m.effect = fxFactory.CreateEffect(info, nullptr);
        m.alpha = (info.alpha < 1.f);
    }


    //--------------------------------------------------------------------------------------
    // Direct3D 9 Vertex Declaration to Direct3D 11 Input Layout mapping
    unsigned int GetInputLayoutDesc(
        _In_reads_(32) const DXUT::D3DVERTEXELEMENT9 decl[],
        std::vector<D3D11_INPUT_ELEMENT_DESC>& inputDesc)
    {
        static const D3D11_INPUT_ELEMENT_DESC s_elements[] =
        {
            { "SV_Position",  0, DXGI_FORMAT_R32G32B32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
            { "NORMAL",       0, DXGI_FORMAT_R32G32B32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
            { "COLOR",        0, DXGI_FORMAT_B8G8R8A8_UNORM,  0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
            { "TANGENT",      0, DXGI_FORMAT_R32G32B32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
            { "BINORMAL",     0, DXGI_FORMAT_R32G32B32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
            { "TEXCOORD",     0, DXGI_FORMAT_R32G32_FLOAT,    0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
            { "BLENDINDICES", 0, DXGI_FORMAT_R8G8B8A8_UINT,   0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
            { "BLENDWEIGHT",  0, DXGI_FORMAT_R8G8B8A8_UNORM,  0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
        };

        using namespace DXUT;

        uint32_t offset = 0;
        uint32_t texcoords = 0;
        unsigned int flags = 0;

        bool posfound = false;

        for (uint32_t index = 0; index < DXUT::MAX_VERTEX_ELEMENTS; ++index)
        {
            if (decl[index].Usage == 0xFF)
                break;

            if (decl[index].Type == D3DDECLTYPE_UNUSED)
                break;

            if (decl[index].Offset != offset)
                break;

            if (decl[index].Usage == D3DDECLUSAGE_POSITION)
            {
                if (decl[index].Type == D3DDECLTYPE_FLOAT3)
                {
                    inputDesc.push_back(s_elements[0]);
                    offset += 12;
                    posfound = true;
                }
                else
                    break;
            }
            else if (decl[index].Usage == D3DDECLUSAGE_NORMAL
                     || decl[index].Usage == D3DDECLUSAGE_TANGENT
                     || decl[index].Usage == D3DDECLUSAGE_BINORMAL)
            {
                size_t base = 1;
                if (decl[index].Usage == D3DDECLUSAGE_TANGENT)
                    base = 3;
                else if (decl[index].Usage == D3DDECLUSAGE_BINORMAL)
                    base = 4;

                D3D11_INPUT_ELEMENT_DESC desc = s_elements[base];

                bool unk = false;
                switch (decl[index].Type)
                {
                    case D3DDECLTYPE_FLOAT3:                 assert(desc.Format == DXGI_FORMAT_R32G32B32_FLOAT); offset += 12; break;
                    case D3DDECLTYPE_UBYTE4N:                desc.Format = DXGI_FORMAT_R8G8B8A8_UNORM; flags |= BIASED_VERTEX_NORMALS; offset += 4; break;
                    case D3DDECLTYPE_SHORT4N:                desc.Format = DXGI_FORMAT_R16G16B16A16_SNORM; offset += 8; break;
                    case D3DDECLTYPE_FLOAT16_4:              desc.Format = DXGI_FORMAT_R16G16B16A16_FLOAT; offset += 8; break;
                    case D3DDECLTYPE_DXGI_R10G10B10A2_UNORM: desc.Format = DXGI_FORMAT_R10G10B10A2_UNORM; flags |= BIASED_VERTEX_NORMALS; offset += 4; break;
                    case D3DDECLTYPE_DXGI_R11G11B10_FLOAT:   desc.Format = DXGI_FORMAT_R11G11B10_FLOAT; flags |= BIASED_VERTEX_NORMALS; offset += 4; break;
                    case D3DDECLTYPE_DXGI_R8G8B8A8_SNORM:    desc.Format = DXGI_FORMAT_R8G8B8A8_SNORM; offset += 4; break;

                    #if defined(_XBOX_ONE) && defined(_TITLE)
                    case D3DDECLTYPE_DEC3N:                  desc.Format = DXGI_FORMAT_R10G10B10_SNORM_A2_UNORM; offset += 4; break;
                    case (32 + DXGI_FORMAT_R10G10B10_SNORM_A2_UNORM): desc.Format = DXGI_FORMAT_R10G10B10_SNORM_A2_UNORM; offset += 4; break;
                    #else
                    case D3DDECLTYPE_DEC3N:                  desc.Format = DXGI_FORMAT_R10G10B10A2_UNORM; flags |= USES_OBSOLETE_DEC3N; offset += 4; break;
                    #endif

                    default:
                        unk = true;
                        break;
                }

                if (unk)
                    break;

                if (decl[index].Usage == D3DDECLUSAGE_TANGENT)
                {
                    flags |= NORMAL_MAPS;
                }

                inputDesc.push_back(desc);
            }
            else if (decl[index].Usage == D3DDECLUSAGE_COLOR)
            {
                D3D11_INPUT_ELEMENT_DESC desc = s_elements[2];

                bool unk = false;
                switch (decl[index].Type)
                {
                    case D3DDECLTYPE_FLOAT4:                 desc.Format = DXGI_FORMAT_R32G32B32A32_FLOAT; offset += 16; break;
                    case D3DDECLTYPE_D3DCOLOR:               assert(desc.Format == DXGI_FORMAT_B8G8R8A8_UNORM); offset += 4; break;
                    case D3DDECLTYPE_UBYTE4N:                desc.Format = DXGI_FORMAT_R8G8B8A8_UNORM; offset += 4; break;
                    case D3DDECLTYPE_FLOAT16_4:              desc.Format = DXGI_FORMAT_R16G16B16A16_FLOAT; offset += 8; break;
                    case D3DDECLTYPE_DXGI_R10G10B10A2_UNORM: desc.Format = DXGI_FORMAT_R10G10B10A2_UNORM; offset += 4; break;
                    case D3DDECLTYPE_DXGI_R11G11B10_FLOAT:   desc.Format = DXGI_FORMAT_R11G11B10_FLOAT; offset += 4; break;

                    default:
                        unk = true;
                        break;
                }

                if (unk)
                    break;

                flags |= PER_VERTEX_COLOR;

                inputDesc.push_back(desc);
            }
            else if (decl[index].Usage == D3DDECLUSAGE_TEXCOORD)
            {
                D3D11_INPUT_ELEMENT_DESC desc = s_elements[5];
                desc.SemanticIndex = decl[index].UsageIndex;

                bool unk = false;
                switch (decl[index].Type)
                {
                    case D3DDECLTYPE_FLOAT1:    desc.Format = DXGI_FORMAT_R32_FLOAT; offset += 4; break;
                    case D3DDECLTYPE_FLOAT2:    assert(desc.Format == DXGI_FORMAT_R32G32_FLOAT); offset += 8; break;
                    case D3DDECLTYPE_FLOAT3:    desc.Format = DXGI_FORMAT_R32G32B32_FLOAT; offset += 12; break;
                    case D3DDECLTYPE_FLOAT4:    desc.Format = DXGI_FORMAT_R32G32B32A32_FLOAT; offset += 16; break;
                    case D3DDECLTYPE_FLOAT16_2: desc.Format = DXGI_FORMAT_R16G16_FLOAT; offset += 4; break;
                    case D3DDECLTYPE_FLOAT16_4: desc.Format = DXGI_FORMAT_R16G16B16A16_FLOAT; offset += 8; break;

                    default:
                        unk = true;
                        break;
                }

                if (unk)
                    break;

                ++texcoords;

                inputDesc.push_back(desc);
            }
            else if (decl[index].Usage == D3DDECLUSAGE_BLENDINDICES)
            {
                if (decl[index].Type == D3DDECLTYPE_UBYTE4)
                {
                    flags |= SKINNING;
                    inputDesc.push_back(s_elements[6]);
                    offset += 4;
                }
                else
                    break;
            }
            else if (decl[index].Usage == D3DDECLUSAGE_BLENDWEIGHT)
            {
                if (decl[index].Type == D3DDECLTYPE_UBYTE4N)
                {
                    flags |= SKINNING;
                    inputDesc.push_back(s_elements[7]);
                    offset += 4;
                }
                else
                    break;
            }
            else
                break;
        }

        if (!posfound)
            throw std::exception();

        if (texcoords == 2)
        {
            flags |= DUAL_TEXTURE;
        }

        return flags;
    }
}


//======================================================================================
// Model Loader
//======================================================================================

_Use_decl_annotations_
std::unique_ptr<Model> DirectX::Model::CreateFromSDKMESH(
    ID3D11Device* d3dDevice,
    const uint8_t* meshData,
    size_t idataSize,
    IEffectFactory& fxFactory,
    ModelLoaderFlags flags)
{
    if (!d3dDevice || !meshData)
        throw std::exception();

    uint64_t dataSize = idataSize;

    // File Headers
    if (dataSize < sizeof(DXUT::SDKMESH_HEADER))
        throw std::exception();
    auto header = reinterpret_cast<const DXUT::SDKMESH_HEADER*>(meshData);

    size_t headerSize = sizeof(DXUT::SDKMESH_HEADER)
        + header->NumVertexBuffers * sizeof(DXUT::SDKMESH_VERTEX_BUFFER_HEADER)
        + header->NumIndexBuffers * sizeof(DXUT::SDKMESH_INDEX_BUFFER_HEADER);
    if (header->HeaderSize != headerSize)
        throw std::exception();

    if (dataSize < header->HeaderSize)
        throw std::exception();

    if (header->Version != DXUT::SDKMESH_FILE_VERSION && header->Version != DXUT::SDKMESH_FILE_VERSION_V2)
        throw std::exception();

    if (header->IsBigEndian)
        throw std::exception();

    if (!header->NumMeshes)
        throw std::exception();

    if (!header->NumVertexBuffers)
        throw std::exception();

    if (!header->NumIndexBuffers)
        throw std::exception();

    if (!header->NumTotalSubsets)
        throw std::exception();

    if (!header->NumMaterials)
        throw std::exception();

    // Sub-headers
    if (dataSize < header->VertexStreamHeadersOffset
        || (dataSize < (header->VertexStreamHeadersOffset + uint64_t(header->NumVertexBuffers) * sizeof(DXUT::SDKMESH_VERTEX_BUFFER_HEADER))))
        throw std::exception();
    auto vbArray = reinterpret_cast<const DXUT::SDKMESH_VERTEX_BUFFER_HEADER*>(meshData + header->VertexStreamHeadersOffset);

    if (dataSize < header->IndexStreamHeadersOffset
        || (dataSize < (header->IndexStreamHeadersOffset + uint64_t(header->NumIndexBuffers) * sizeof(DXUT::SDKMESH_INDEX_BUFFER_HEADER))))
        throw std::exception();
    auto ibArray = reinterpret_cast<const DXUT::SDKMESH_INDEX_BUFFER_HEADER*>(meshData + header->IndexStreamHeadersOffset);

    if (dataSize < header->MeshDataOffset
        || (dataSize < (header->MeshDataOffset + uint64_t(header->NumMeshes) * sizeof(DXUT::SDKMESH_MESH))))
        throw std::exception();
    auto meshArray = reinterpret_cast<const DXUT::SDKMESH_MESH*>(meshData + header->MeshDataOffset);

    if (dataSize < header->SubsetDataOffset
        || (dataSize < (header->SubsetDataOffset + uint64_t(header->NumTotalSubsets) * sizeof(DXUT::SDKMESH_SUBSET))))
        throw std::exception();
    auto subsetArray = reinterpret_cast<const DXUT::SDKMESH_SUBSET*>(meshData + header->SubsetDataOffset);

    if (dataSize < header->FrameDataOffset
        || (dataSize < (header->FrameDataOffset + uint64_t(header->NumFrames) * sizeof(DXUT::SDKMESH_FRAME))))
        throw std::exception();
    // TODO - auto frameArray = reinterpret_cast<const DXUT::SDKMESH_FRAME*>( meshData + header->FrameDataOffset );

    if (dataSize < header->MaterialDataOffset
        || (dataSize < (header->MaterialDataOffset + uint64_t(header->NumMaterials) * sizeof(DXUT::SDKMESH_MATERIAL))))
        throw std::exception();

    const DXUT::SDKMESH_MATERIAL* materialArray = nullptr;
    const DXUT::SDKMESH_MATERIAL_V2* materialArray_v2 = nullptr;
    if (header->Version == DXUT::SDKMESH_FILE_VERSION_V2)
    {
        materialArray_v2 = reinterpret_cast<const DXUT::SDKMESH_MATERIAL_V2*>(meshData + header->MaterialDataOffset);
    }
    else
    {
        materialArray = reinterpret_cast<const DXUT::SDKMESH_MATERIAL*>(meshData + header->MaterialDataOffset);
    }

    // Buffer data
    uint64_t bufferDataOffset = header->HeaderSize + header->NonBufferDataSize;
    if ((dataSize < bufferDataOffset)
        || (dataSize < bufferDataOffset + header->BufferDataSize))
        throw std::exception();
    const uint8_t* bufferData = meshData + bufferDataOffset;

    // Create vertex buffers
    std::vector<ComPtr<ID3D11Buffer>> vbs;
    vbs.resize(header->NumVertexBuffers);

    std::vector<std::shared_ptr<std::vector<D3D11_INPUT_ELEMENT_DESC>>> vbDecls;
    vbDecls.resize(header->NumVertexBuffers);

    std::vector<unsigned int> materialFlags;
    materialFlags.resize(header->NumVertexBuffers);

    bool dec3nwarning = false;
    for (UINT j = 0; j < header->NumVertexBuffers; ++j)
    {
        auto& vh = vbArray[j];

        if (vh.SizeBytes > UINT32_MAX)
            throw std::exception();

        if (!(flags & ModelLoader_AllowLargeModels))
        {
            if (vh.SizeBytes > (D3D11_REQ_RESOURCE_SIZE_IN_MEGABYTES_EXPRESSION_A_TERM * 1024u * 1024u))
                throw std::exception();
        }

        if (dataSize < vh.DataOffset
            || (dataSize < vh.DataOffset + vh.SizeBytes))
            throw std::exception();

        vbDecls[j] = std::make_shared<std::vector<D3D11_INPUT_ELEMENT_DESC>>();
        unsigned int ilflags = GetInputLayoutDesc(vh.Decl, *vbDecls[j].get());

        if (ilflags & SKINNING)
        {
            ilflags &= ~static_cast<unsigned int>(DUAL_TEXTURE | NORMAL_MAPS);
        }
        if (ilflags & DUAL_TEXTURE)
        {
            ilflags &= ~static_cast<unsigned int>(NORMAL_MAPS);
        }

        if (ilflags & USES_OBSOLETE_DEC3N)
        {
            dec3nwarning = true;
        }

        materialFlags[j] = ilflags;

        auto verts = bufferData + (vh.DataOffset - bufferDataOffset);

        D3D11_BUFFER_DESC desc = {};
        desc.Usage = D3D11_USAGE_DEFAULT;
        desc.ByteWidth = static_cast<UINT>(vh.SizeBytes);
        desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;

        D3D11_SUBRESOURCE_DATA initData = { verts, 0, 0 };

        ThrowIfFailed(
            d3dDevice->CreateBuffer(&desc, &initData, &vbs[j])
        );

        SetDebugObjectName(vbs[j].Get(), "ModelSDKMESH");
    }

    if (dec3nwarning)
    {
        DebugTrace("WARNING: Vertex declaration uses legacy Direct3D 9 D3DDECLTYPE_DEC3N which has no DXGI equivalent\n"
                   "         (treating as DXGI_FORMAT_R10G10B10A2_UNORM which is not a signed format)\n");
    }

    // Create index buffers
    std::vector<ComPtr<ID3D11Buffer>> ibs;
    ibs.resize(header->NumIndexBuffers);

    for (UINT j = 0; j < header->NumIndexBuffers; ++j)
    {
        auto& ih = ibArray[j];

        if (ih.SizeBytes > UINT32_MAX)
            throw std::exception();

        if (!(flags & ModelLoader_AllowLargeModels))
        {
            if (ih.SizeBytes > (D3D11_REQ_RESOURCE_SIZE_IN_MEGABYTES_EXPRESSION_A_TERM * 1024u * 1024u))
                throw std::exception();
        }

        if (dataSize < ih.DataOffset
            || (dataSize < ih.DataOffset + ih.SizeBytes))
            throw std::exception();

        if (ih.IndexType != DXUT::IT_16BIT && ih.IndexType != DXUT::IT_32BIT)
            throw std::exception();

        auto indices = bufferData + (ih.DataOffset - bufferDataOffset);

        D3D11_BUFFER_DESC desc = {};
        desc.Usage = D3D11_USAGE_DEFAULT;
        desc.ByteWidth = static_cast<UINT>(ih.SizeBytes);
        desc.BindFlags = D3D11_BIND_INDEX_BUFFER;

        D3D11_SUBRESOURCE_DATA initData = { indices, 0, 0 };

        ThrowIfFailed(
            d3dDevice->CreateBuffer(&desc, &initData, &ibs[j])
        );

        SetDebugObjectName(ibs[j].Get(), "ModelSDKMESH");
    }

    // Create meshes
    std::vector<MaterialRecordSDKMESH> materials;
    materials.resize(header->NumMaterials);

    auto model = std::make_unique<Model>();
    model->meshes.reserve(header->NumMeshes);

    for (UINT meshIndex = 0; meshIndex < header->NumMeshes; ++meshIndex)
    {
        auto& mh = meshArray[meshIndex];

        if (!mh.NumSubsets
            || !mh.NumVertexBuffers
            || mh.IndexBuffer >= header->NumIndexBuffers
            || mh.VertexBuffers[0] >= header->NumVertexBuffers)
            throw std::exception();

        // mh.NumVertexBuffers is sometimes not what you'd expect, so we skip validating it

        if (dataSize < mh.SubsetOffset
            || (dataSize < mh.SubsetOffset + uint64_t(mh.NumSubsets) * sizeof(UINT)))
            throw std::exception();

        auto subsets = reinterpret_cast<const UINT*>(meshData + mh.SubsetOffset);

        if (mh.NumFrameInfluences > 0)
        {
            if (dataSize < mh.FrameInfluenceOffset
                || (dataSize < mh.FrameInfluenceOffset + uint64_t(mh.NumFrameInfluences) * sizeof(UINT)))
                throw std::exception();

            // TODO - auto influences = reinterpret_cast<const UINT*>( meshData + mh.FrameInfluenceOffset );
        }

        auto mesh = std::make_shared<ModelMesh>();
        wchar_t meshName[DXUT::MAX_MESH_NAME] = {};
        MultiByteToWideChar(CP_UTF8, 0, mh.Name, -1, meshName, DXUT::MAX_MESH_NAME);
        mesh->name = meshName;
        mesh->ccw = (flags & ModelLoader_CounterClockwise) != 0;
        mesh->pmalpha = (flags & ModelLoader_PremultipledAlpha) != 0;

        // Extents
        mesh->boundingBox.Center = mh.BoundingBoxCenter;
        mesh->boundingBox.Extents = mh.BoundingBoxExtents;
        BoundingSphere::CreateFromBoundingBox(mesh->boundingSphere, mesh->boundingBox);

        // Create subsets
        mesh->meshParts.reserve(mh.NumSubsets);
        for (UINT j = 0; j < mh.NumSubsets; ++j)
        {
            auto sIndex = subsets[j];
            if (sIndex >= header->NumTotalSubsets)
                throw std::exception();

            auto& subset = subsetArray[sIndex];

            D3D11_PRIMITIVE_TOPOLOGY primType;
            switch (subset.PrimitiveType)
            {
                case DXUT::PT_TRIANGLE_LIST:        primType = D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST;       break;
                case DXUT::PT_TRIANGLE_STRIP:       primType = D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP;      break;
                case DXUT::PT_LINE_LIST:            primType = D3D11_PRIMITIVE_TOPOLOGY_LINELIST;           break;
                case DXUT::PT_LINE_STRIP:           primType = D3D11_PRIMITIVE_TOPOLOGY_LINESTRIP;          break;
                case DXUT::PT_POINT_LIST:           primType = D3D11_PRIMITIVE_TOPOLOGY_POINTLIST;          break;
                case DXUT::PT_TRIANGLE_LIST_ADJ:    primType = D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST_ADJ;   break;
                case DXUT::PT_TRIANGLE_STRIP_ADJ:   primType = D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP_ADJ;  break;
                case DXUT::PT_LINE_LIST_ADJ:        primType = D3D11_PRIMITIVE_TOPOLOGY_LINELIST_ADJ;       break;
                case DXUT::PT_LINE_STRIP_ADJ:       primType = D3D11_PRIMITIVE_TOPOLOGY_LINESTRIP_ADJ;      break;

                case DXUT::PT_QUAD_PATCH_LIST:
                case DXUT::PT_TRIANGLE_PATCH_LIST:
                    throw std::exception();

                default:
                    throw std::exception();
            }

            if (subset.MaterialID >= header->NumMaterials)
                throw std::exception();

            auto& mat = materials[subset.MaterialID];

            if (!mat.effect)
            {
                size_t vi = mh.VertexBuffers[0];

                if (materialArray_v2)
                {
                    LoadMaterial(
                        materialArray_v2[subset.MaterialID],
                        materialFlags[vi],
                        fxFactory,
                        mat);
                }
                else
                {
                    LoadMaterial(
                        materialArray[subset.MaterialID],
                        materialFlags[vi],
                        fxFactory,
                        mat,
                        (flags & ModelLoader_MaterialColorsSRGB) != 0);
                }
            }

            ComPtr<ID3D11InputLayout> il;
            ThrowIfFailed(
                CreateInputLayoutFromEffect(d3dDevice, mat.effect.get(),
                    vbDecls[mh.VertexBuffers[0]]->data(), vbDecls[mh.VertexBuffers[0]]->size(), il.GetAddressOf())
            );

            SetDebugObjectName(il.Get(), "ModelSDKMESH");

            auto part = new ModelMeshPart();
            part->isAlpha = mat.alpha;

            part->indexCount = static_cast<uint32_t>(subset.IndexCount);
            part->startIndex = static_cast<uint32_t>(subset.IndexStart);
            part->vertexOffset = static_cast<int32_t>(subset.VertexStart);
            part->vertexStride = static_cast<uint32_t>(vbArray[mh.VertexBuffers[0]].StrideBytes);
            part->indexFormat = (ibArray[mh.IndexBuffer].IndexType == DXUT::IT_32BIT) ? DXGI_FORMAT_R32_UINT : DXGI_FORMAT_R16_UINT;
            part->primitiveType = primType;
            part->inputLayout = il;
            part->indexBuffer = ibs[mh.IndexBuffer];
            part->vertexBuffer = vbs[mh.VertexBuffers[0]];
            part->effect = mat.effect;
            part->vbDecl = vbDecls[mh.VertexBuffers[0]];

            mesh->meshParts.emplace_back(part);
        }

        model->meshes.emplace_back(mesh);
    }

    return model;
}


//--------------------------------------------------------------------------------------
_Use_decl_annotations_
std::unique_ptr<Model> DirectX::Model::CreateFromSDKMESH(
    ID3D11Device* device,
    const wchar_t* szFileName,
    IEffectFactory& fxFactory,
    ModelLoaderFlags flags)
{
    size_t dataSize = 0;
    std::unique_ptr<uint8_t[]> data;
    HRESULT hr = BinaryReader::ReadEntireFile(szFileName, data, &dataSize);
    if (FAILED(hr))
    {
        DebugTrace("ERROR: CreateFromSDKMESH failed (%08X) loading '%ls'\n",
            static_cast<unsigned int>(hr), szFileName);
        throw std::exception();
    }

    auto model = CreateFromSDKMESH(device, data.get(), dataSize, fxFactory, flags);

    model->name = szFileName;

    return model;
}