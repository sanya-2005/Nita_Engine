#include "RenderEngine.h"
#include "SimpleMeshRender.h"
#include "GPUResourceStatistic.h"
#include "Log.h"
#include "D3D11Utils.h"

using namespace DirectX;
using namespace D3DUtils;
using namespace GPU;

#include <DirectXMath.h>
#include <DirectXColors.h>
#include <vector>


bool RenderEngine::Init(OSWindow& osWindow)
{
    std::string logTitle = "Render Engine";

    this->osWindow = &osWindow;

    device = new RenderDevice();

    context = new RenderContext();

    if (!device->Init(osWindow, *context))
    {
        logger->WriteLine("Error initializating Render Device", logTitle);
        return false;
    }

    data = new RenderData(osWindow);

    Texture2D* backbuffer = device->GetBackBuffer();

    if (!backbuffer)
    {
        logger->WriteLine("Error create Back Buffer for render target", logTitle);
        return false;
    }

    outputRenderTarget = device->CreateRenderTarget(backbuffer);

    if (!outputRenderTarget)
    {
        logger->WriteLine("Error create Render target View", logTitle);
        return false;
    }

    delete backbuffer;

    Size size = osWindow.GetWindowSize();

    depthStencilBuffer = device->CreateTexture2D(DepthStencilMode, size, ZBuffer_32Bit);

    if (!depthStencilBuffer)
    {
        logger->WriteLine("Error create Texture2D for depth stencil Buffer", logTitle);
        return false;
    }

    depthStencilView = device->CreateDepthStencil(depthStencilBuffer);

    if (!depthStencilView)
    {
        logger->WriteLine("Error create Depth Stencil View", logTitle);
        return false;
    }

    D3D11_DEPTH_STENCIL_DESC depthStencilStateDesc;
    ZeroMemory(&depthStencilStateDesc, sizeof(D3D11_DEPTH_STENCIL_DESC));

    depthStencilStateDesc.DepthEnable = true;
    depthStencilStateDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
    depthStencilStateDesc.DepthFunc = D3D11_COMPARISON_LESS;
    depthStencilStateDesc.StencilEnable = false;

    HRESULT hr = device->GetDeviceHandle()->CreateDepthStencilState(&depthStencilStateDesc, &depthStencilState);

    if (FAILED(hr))
    {
        logger->WriteLine("Error Creating Depth Stencil State", logTitle);
        return false;
    }

    viewport = new D3D11_VIEWPORT();

    viewport->Width = static_cast<float>(size.width);
    viewport->Height = static_cast<float>(size.height);
    viewport->TopLeftX = 0.0f;
    viewport->TopLeftY = 0.0f;
    viewport->MinDepth = 0.0f;
    viewport->MaxDepth = 1.0f;

    firstRender = new SimpleMeshRender();

    if (!firstRender->Init(*device))
    {
        logger->WriteLine("Error Initializating Simple Mesh Render", logTitle);
        return false;
    }

    return true;
}

void RenderEngine::Render()
{
    Color color = {0.5f, 0.6f, 0.1f, 1.0f};

    context->SetViewport(*viewport);

    context->SetRenderTarget(outputRenderTarget, depthStencilView);

    context->GetContextHandle()->OMSetDepthStencilState(depthStencilState, 1);

    Clear(color);

    firstRender->Prepare(*context);
    firstRender->Render(*device);

    device->SwapBuffers();
}

void RenderEngine::Clear(Color& clearColor)
{
    context->GetContextHandle()->ClearRenderTargetView((ID3D11RenderTargetView*)outputRenderTarget->GetHandle(), clearColor.GetArray());
    context->GetContextHandle()->ClearDepthStencilView((ID3D11DepthStencilView*)depthStencilView->GetHandle(), D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);
}

void RenderEngine::Update()
{
    firstRender->LoadData(*device, *data);
}

void RenderEngine::Resize(uint newWitdh, uint newHeight)
{
    //иногда (например при сворачивании окна) размер окна будет 0. тогда стоит скипнуть изменение размера
    if (newWitdh == 0 || newHeight == 0)
    {
        return;
    }

    std::string logTitle = "RenderEngine::Resize";

    context->ClearRenderTarget();

    delete outputRenderTarget;
    outputRenderTarget = nullptr;

    delete depthStencilBuffer;
    depthStencilBuffer = nullptr;

    delete depthStencilView;
    depthStencilView = nullptr;

    device->Flush();

    device->Resize(newWitdh, newHeight);

    Texture2D* backbuffer = device->GetBackBuffer();

    if (!backbuffer)
    {
        logger->WriteLine("Error create Back Buffer for render target", logTitle);
        return;
    }

    outputRenderTarget = device->CreateRenderTarget(backbuffer);

    if (!outputRenderTarget)
    {
        logger->WriteLine("Error create Render target View", logTitle);
        return;
    }

    delete backbuffer;

    Size size{};

    size.height = newHeight;
    size.width = newWitdh;

    depthStencilBuffer = device->CreateTexture2D(DepthStencilMode, size, ZBuffer_32Bit);

    if (!depthStencilBuffer)
    {
        logger->WriteLine("Error create Texture2D for depth stencil Buffer", logTitle);
    }

    depthStencilView = device->CreateDepthStencil(depthStencilBuffer);

    if (!depthStencilView)
    {
        logger->WriteLine("Error create Depth Stencil View", logTitle);
    }

    viewport->Width = (float)newWitdh;
    viewport->Height = (float)newHeight;

    float aspect = (float)newWitdh / (float)newHeight;

    if (aspect < 0.01f)
    {
        aspect = 0.0f;
    }

    data->projectionMatrix = XMMatrixPerspectiveFovLH(XMConvertToRadians(90.0f), aspect, 0.1f, 1000.0f);
}

void RenderEngine::Resize(Size& size)
{
    Resize(size.width, size.height);
}

void RenderEngine::Destroy()
{
    firstRender->Destroy();

    delete outputRenderTarget;
    delete depthStencilView;

    SafeRelease(depthStencilState);

    delete depthStencilBuffer;
    delete viewport;

    delete context;
    delete device;

}