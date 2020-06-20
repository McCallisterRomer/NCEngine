//--------------------------------------------------------------------------------------
// File: ModelLoadVBO.cpp
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

#include "vbo.h"

using namespace DirectX;
using Microsoft::WRL::ComPtr;

static_assert(sizeof(VertexPositionNormalTexture) == 32, "VBO vertex size mismatch");

namespace
{
    //--------------------------------------------------------------------------------------
    // Shared VB input element description
    INIT_ONCE g_InitOnce = INIT_ONCE_STATIC_INIT;
    std::shared_ptr<std::vector<D3D11_INPUT_ELEMENT_DESC>> g_vbdecl;

    BOOL CALLBACK InitializeDecl(PINIT_ONCE initOnce, PVOID Parameter, PVOID *lpContext)
    {
        UNREFERENCED_PARAMETER(initOnce);
        UNREFERENCED_PARAMETER(Parameter);
        UNREFERENCED_PARAMETER(lpContext);

        g_vbdecl = std::make_shared<std::vector<D3D11_INPUT_ELEMENT_DESC>>(
            VertexPositionNormalTexture::InputElements,
            VertexPositionNormalTexture::InputElements + VertexPositionNormalTexture::InputElementCount);

        return TRUE;
    }

    BOOL InitOnceExecuteOnce(
        PINIT_ONCE    InitOnce,
        PINIT_ONCE_FN InitFn,
        PVOID         Context,
        LPVOID        *Parameter
    );
}


//--------------------------------------------------------------------------------------
_Use_decl_annotations_
std::unique_ptr<Model> DirectX::Model::CreateFromVBO(
    ID3D11Device* device,
    const uint8_t* meshData, size_t dataSize,
    std::shared_ptr<IEffect> ieffect,
    ModelLoaderFlags flags)
{
    if (!InitOnceExecuteOnce(&g_InitOnce, InitializeDecl, nullptr, nullptr))
        throw std::exception();

    if (!device || !meshData)
        throw std::exception();

    // File Header
    if (dataSize < sizeof(VBO::header_t))
        throw std::exception();
    auto header = reinterpret_cast<const VBO::header_t*>(meshData);

    if (!header->numVertices || !header->numIndices)
        throw std::exception();

    uint64_t sizeInBytes = uint64_t(header->numVertices) * sizeof(VertexPositionNormalTexture);

    if (sizeInBytes > UINT32_MAX)
        throw std::exception();

    if (!(flags & ModelLoader_AllowLargeModels))
    {
        if (sizeInBytes > uint64_t(D3D11_REQ_RESOURCE_SIZE_IN_MEGABYTES_EXPRESSION_A_TERM * 1024u * 1024u))
            throw std::exception();
    }

    auto vertSize = static_cast<size_t>(sizeInBytes);

    if (dataSize < (vertSize + sizeof(VBO::header_t)))
        throw std::exception();
    auto verts = reinterpret_cast<const VertexPositionNormalTexture*>(meshData + sizeof(VBO::header_t));

    sizeInBytes = uint64_t(header->numIndices) * sizeof(uint16_t);

    if (sizeInBytes > UINT32_MAX)
        throw std::exception();

    if (!(flags & ModelLoader_AllowLargeModels))
    {
        if (sizeInBytes > uint64_t(D3D11_REQ_RESOURCE_SIZE_IN_MEGABYTES_EXPRESSION_A_TERM * 1024u * 1024u))
            throw std::exception();
    }

    auto indexSize = static_cast<size_t>(sizeInBytes);

    if (dataSize < (sizeof(VBO::header_t) + vertSize + indexSize))
        throw std::exception();
    auto indices = reinterpret_cast<const uint16_t*>(meshData + sizeof(VBO::header_t) + vertSize);

    // Create vertex buffer
    ComPtr<ID3D11Buffer> vb;
    {
        D3D11_BUFFER_DESC desc = {};
        desc.Usage = D3D11_USAGE_DEFAULT;
        desc.ByteWidth = static_cast<UINT>(vertSize);
        desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;

        D3D11_SUBRESOURCE_DATA initData = { verts, 0, 0 };

        ThrowIfFailed(
            device->CreateBuffer(&desc, &initData, vb.GetAddressOf())
        );

        SetDebugObjectName(vb.Get(), "ModelVBO");
    }

    // Create index buffer
    ComPtr<ID3D11Buffer> ib;
    {
        D3D11_BUFFER_DESC desc = {};
        desc.Usage = D3D11_USAGE_DEFAULT;
        desc.ByteWidth = static_cast<UINT>(indexSize);
        desc.BindFlags = D3D11_BIND_INDEX_BUFFER;

        D3D11_SUBRESOURCE_DATA initData = { indices, 0, 0 };

        ThrowIfFailed(
            device->CreateBuffer(&desc, &initData, ib.GetAddressOf())
        );

        SetDebugObjectName(ib.Get(), "ModelVBO");
    }

    // Create input layout and effect
    if (!ieffect)
    {
        auto effect = std::make_shared<BasicEffect>(device);
        effect->EnableDefaultLighting();
        effect->SetLightingEnabled(true);

        ieffect = effect;
    }

    ComPtr<ID3D11InputLayout> il;

    ThrowIfFailed(
        CreateInputLayoutFromEffect<VertexPositionNormalTexture>(device, ieffect.get(), il.GetAddressOf())
    );

    SetDebugObjectName(il.Get(), "ModelVBO");

    auto part = new ModelMeshPart();
    part->indexCount = header->numIndices;
    part->startIndex = 0;
    part->vertexStride = static_cast<UINT>(sizeof(VertexPositionNormalTexture));
    part->inputLayout = il;
    part->indexBuffer = ib;
    part->vertexBuffer = vb;
    part->effect = ieffect;
    part->vbDecl = g_vbdecl;

    auto mesh = std::make_shared<ModelMesh>();
    mesh->ccw = (flags & ModelLoader_CounterClockwise) != 0;
    mesh->pmalpha = (flags & ModelLoader_PremultipledAlpha) != 0;
    BoundingSphere::CreateFromPoints(mesh->boundingSphere, header->numVertices, &verts->position, sizeof(VertexPositionNormalTexture));
    BoundingBox::CreateFromPoints(mesh->boundingBox, header->numVertices, &verts->position, sizeof(VertexPositionNormalTexture));
    mesh->meshParts.emplace_back(part);

    auto model = std::make_unique<Model>();
    model->meshes.emplace_back(mesh);

    return model;
}


//--------------------------------------------------------------------------------------
_Use_decl_annotations_
std::unique_ptr<Model> DirectX::Model::CreateFromVBO(
    ID3D11Device* device,
    const wchar_t* szFileName,
    std::shared_ptr<IEffect> ieffect,
    ModelLoaderFlags flags)
{
    size_t dataSize = 0;
    std::unique_ptr<uint8_t[]> data;
    HRESULT hr = BinaryReader::ReadEntireFile(szFileName, data, &dataSize);
    if (FAILED(hr))
    {
        DebugTrace("ERROR: CreateFromVBO failed (%08X) loading '%ls'\n",
            static_cast<unsigned int>(hr), szFileName);
        throw std::exception();
    }

    auto model = CreateFromVBO(device, data.get(), dataSize, ieffect, flags);

    model->name = szFileName;

    return model;
}