#pragma once
#include "OSWindow.h"
#include "Win32Utils.h"
#include "RenderDevice.h"

#include <DirectXMath.h>

//struct VertexPosColor
//{
//    XMFLOAT3 Position;
//    XMFLOAT3 Color;
//    XMFLOAT2 uv;
//};
//
//static VertexPosColor g_Vertices[8] =
//{
//    { XMFLOAT3(-1.0f, -1.0f, -1.0f), XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT2(0.0f, 0.0f) }, // 0
//    { XMFLOAT3(-1.0f,  1.0f, -1.0f), XMFLOAT3(0.0f, 1.0f, 0.0f), XMFLOAT2(1.0f, 0.0f) }, // 1
//    { XMFLOAT3(1.0f,  1.0f, -1.0f), XMFLOAT3(1.0f, 1.0f, 0.0f), XMFLOAT2(0.0f, 1.0f) }, // 2
//    { XMFLOAT3(1.0f, -1.0f, -1.0f), XMFLOAT3(1.0f, 0.0f, 0.0f), XMFLOAT2(1.0f, 1.0f) }, // 3
//    { XMFLOAT3(-1.0f, -1.0f,  1.0f), XMFLOAT3(0.0f, 0.0f, 1.0f), XMFLOAT2(0.0f, 0.0f) }, // 4
//    { XMFLOAT3(-1.0f,  1.0f,  1.0f), XMFLOAT3(0.0f, 1.0f, 1.0f), XMFLOAT2(1.0f, 0.0f) }, // 5
//    { XMFLOAT3(1.0f,  1.0f,  1.0f), XMFLOAT3(1.0f, 1.0f, 1.0f), XMFLOAT2(0.0f, 1.0f) }, // 6
//    { XMFLOAT3(1.0f, -1.0f,  1.0f), XMFLOAT3(1.0f, 0.0f, 1.0f), XMFLOAT2(1.0f, 1.0f) }  // 7
//};
//
//static unsigned short g_Indicies[36] =
//{
//    0, 1, 2, 0, 2, 3,
//    4, 6, 5, 4, 7, 6,
//    4, 5, 1, 4, 1, 0,
//    3, 2, 6, 3, 6, 7,
//    1, 5, 6, 1, 6, 2,
//    4, 0, 3, 4, 3, 7
//};

class Level;

class RenderData
{
public:
    OSWindow* window;
    Level* level;

	DirectX::XMMATRIX viewMatrix;
    DirectX::XMMATRIX projectionMatrix;

    RenderData(OSWindow& window)
    {
        this->window = &window;
        level = nullptr;

        Size size = window.GetWindowSize();

        projectionMatrix = DirectX::XMMatrixPerspectiveFovLH(DirectX::XMConvertToRadians(45.0f), (float)size.width / (float)size.height, 0.1f, 100.0f);
        
        DirectX::XMVECTOR eyePosition = DirectX::XMVectorSet(2, 0, -10, 1);
        DirectX::XMVECTOR focusPoint = DirectX::XMVectorSet(0, 0, 0, 1);
        DirectX::XMVECTOR upDirection = DirectX::XMVectorSet(0, 1, 0, 0);

        viewMatrix = DirectX::XMMatrixLookAtLH(eyePosition, focusPoint, upDirection);
    }
};

class IRender
{
public:
	virtual bool Init(GPU::RenderDevice& device) = 0;
    virtual void Prepare(GPU::RenderContext& context) = 0;
	virtual void LoadData(GPU::RenderDevice& device, RenderData& data) = 0;

	virtual void Render(GPU::RenderDevice& device) = 0;
	virtual void Destroy() = 0;
};