#include "RenderDevice.h"
#include "OSWindow.h"
#include "Log.h"
#include "GPUResourceStatistic.h"

#include <d3d11.h>
#include <dxgicommon.h >

namespace GPU
{
    bool RenderDevice::Init(OSWindow& osWindow, RenderContext& context)
    {
        std::string logTitle = "GPU";

        this->context = &context;

        DXGI_SWAP_CHAIN_DESC swapChainDesc;
        ZeroMemory(&swapChainDesc, sizeof(DXGI_SWAP_CHAIN_DESC));

        Size size = osWindow.GetWindowSize();

        swapChainDesc.BufferCount = 2;
        swapChainDesc.BufferDesc.Width = size.width;
        swapChainDesc.BufferDesc.Height = size.height;
        swapChainDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
        swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
        swapChainDesc.OutputWindow = static_cast<HWND>(osWindow.GetWindowHandle());
        swapChainDesc.SampleDesc.Count = 1;
        swapChainDesc.SampleDesc.Quality = 0;
        swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_FLIP_SEQUENTIAL;
        swapChainDesc.Windowed = true;

#ifdef DEBUG
        uint createDeviceFlags = D3D11_CREATE_DEVICE_DEBUG;
#else
        uint createDeviceFlags = 0;
#endif


        std::vector<D3D_FEATURE_LEVEL> featureLevels{ D3D_FEATURE_LEVEL_11_1, D3D_FEATURE_LEVEL_11_0 , D3D_FEATURE_LEVEL_10_1,
                                                        D3D_FEATURE_LEVEL_10_0, D3D_FEATURE_LEVEL_9_3,
                                                        D3D_FEATURE_LEVEL_9_2, D3D_FEATURE_LEVEL_9_1
        };

        D3D_FEATURE_LEVEL featureLevel;

        logger->WriteLine("Initializating Device and Swap Chain", logTitle);

        ID3D11DeviceContext* deviceContext;

        HRESULT hr = D3D11CreateDeviceAndSwapChain(nullptr, D3D_DRIVER_TYPE_HARDWARE,
                                                   nullptr, createDeviceFlags, featureLevels.data(), (uint)featureLevels.size(),
                                                   D3D11_SDK_VERSION, &swapChainDesc, &swapChain, &device, &featureLevel,
                                                   &deviceContext);

        this->context->contextHandle = deviceContext;

        if (FAILED(hr))
        {
            logger->WriteLine("Error Initializating Device and Swap Chain", logTitle);
            return false;
        }

        return true;
    }

    RenderTargetHandle* RenderDevice::CreateRenderTarget(Texture2D* texture)
    {
        ID3D11RenderTargetView* renderTarget;

        HRESULT hr = device->CreateRenderTargetView((ID3D11Resource*)texture->GetHandle(), nullptr, &renderTarget);

        if (FAILED(hr))
        {
            logger->WriteLine("Error create RenderTarget", "GPU");
            return nullptr;
        }

        RenderTargetHandle* target = new RenderTargetHandle(renderTarget);

        return target;
    }

    DepthStencilBuffer* RenderDevice::CreateDepthStencil(Texture2D* texture)
    {
        ID3D11DepthStencilView* handle;

        HRESULT hr = device->CreateDepthStencilView((ID3D11Resource*)texture->GetHandle(), nullptr, &handle);

        if (FAILED(hr))
        {
            logger->WriteLine("Error create Depth Stencil", "GPU");
            return nullptr;
        }

        DepthStencilBuffer* depthStencil = new DepthStencilBuffer(handle);

        return depthStencil;
    }

    Texture2D* RenderDevice::GetBackBuffer()
    {
        ID3D11Texture2D* backBuffer = nullptr;

        HRESULT hr = swapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)&backBuffer);

        if (FAILED(hr))
        {
            logger->WriteLine("Error get back buffer from Swap chain", "GPU");
            return nullptr;
        }

        Texture2D* texture = new Texture2D(backBuffer);
        stats->AddResource((uintptr_t)backBuffer, "Texture 2D (Back Buffer)");

        return texture;
    }

    Texture2D* RenderDevice::CreateTexture2D(TextureBindMode mode, Size size, GPUFormat format)
    {
        ID3D11Texture2D* texture;

        D3D11_TEXTURE2D_DESC texture2Ddesc;
        ZeroMemory(&texture2Ddesc, sizeof(D3D11_TEXTURE2D_DESC));

        texture2Ddesc.ArraySize = 1;
        texture2Ddesc.BindFlags = mode;
        texture2Ddesc.CPUAccessFlags = 0;
        texture2Ddesc.Format = static_cast<DXGI_FORMAT>(format);
        texture2Ddesc.Width = size.width;
        texture2Ddesc.Height = size.height;
        texture2Ddesc.MipLevels = 1;
        texture2Ddesc.SampleDesc.Count = 1;
        texture2Ddesc.SampleDesc.Quality = 0;
        texture2Ddesc.Usage = D3D11_USAGE_DEFAULT;

        HRESULT hr = device->CreateTexture2D(&texture2Ddesc, nullptr, &texture);

        if (FAILED(hr))
        {
            logger->WriteLine("Error Creating Texture2D", "GPU");
            return nullptr;
        }

        Texture2D* result = new Texture2D(texture);

        stats->AddResource((uintptr_t)texture, "Texture 2D");

        return result;
    }

    VertexFormat* RenderDevice::CreateVertexFormat(VertexAttribute* attributesArray, uint arraySize, ShaderBytecode& code)
    {
        ID3D11InputLayout* layout;

        std::vector<D3D11_INPUT_ELEMENT_DESC> decs;

        for (int i = 0; i < (int)arraySize; i++)
        {
            decs.push_back(attributesArray[i].ConvertToD3dInputElement());
        }

        HRESULT hr = device->CreateInputLayout(decs.data(), arraySize, code.data, code.size, &layout);

        if (FAILED(hr))
        {
            logger->WriteLine("Error create Input Layout", "GPU");

            return nullptr;
        }

        VertexFormat* format = new VertexFormat(layout);
        stats->AddResource((uintptr_t)layout, "Vertex Format");

        return format;
    }

    void RenderDevice::UpdateSubResource(GPUResource& resource, void* data)
    {
        ID3D11DeviceContext* handle = context->GetContextHandle();

        handle->UpdateSubresource((ID3D11Resource*)resource.GetHandle(), 0, nullptr, data, 0, 0);
    }

    void RenderDevice::SwapBuffers()
    {
        swapChain->Present(1, 0);
    }

    void RenderDevice::Resize(uint width, uint height)
    {
        HRESULT hr = swapChain->ResizeBuffers(2, width, height, DXGI_FORMAT_UNKNOWN, 0);

        if (FAILED(hr))
        {
            logger->WriteLine("Error Resize Buffers", "GPU");
        }
    }

    void RenderDevice::Flush()
    {
        context->GetContextHandle()->Flush();
    }

    void RenderDevice::DrawIndexed(uint count)
    {
        context->GetContextHandle()->DrawIndexed(count, 0, 0);
    }

    template<>
    VertexShader* RenderDevice::CreateShader<VertexShader>(ShaderBytecode& code)
    {
        ID3D11VertexShader* shaderHandle;

        HRESULT hr = device->CreateVertexShader(code.data, code.size, nullptr, &shaderHandle);

        if (FAILED(hr))
        {
            logger->WriteLine("Error create Vertex Shader", "GPU");
            return nullptr;
        }

        VertexShader* shader = new VertexShader(shaderHandle);

        stats->AddResource((uintptr_t)shaderHandle, "Vertex Shader");

        return shader;
    }

    template<>
    PixelShader* RenderDevice::CreateShader<PixelShader>(ShaderBytecode& code)
    {
        ID3D11PixelShader* shaderHandle;

        HRESULT hr = device->CreatePixelShader(code.data, code.size, nullptr, &shaderHandle);

        if (FAILED(hr))
        {
            logger->WriteLine("Error create Pixel Shader", "GPU");
            return nullptr;
        }

        PixelShader* shader = new PixelShader(shaderHandle);

        stats->AddResource((uintptr_t)shaderHandle, "Pixel Shader");

        return shader;
    }

    static ID3D11Buffer* CreateBufferHandleWithSubresource(ID3D11Device* device, D3D11_BIND_FLAG flag, BufferUsage usage, size_t size, uint CPUAccessFlag, void* bufferData)
    {
        D3D11_BUFFER_DESC bufferDesc;
        ZeroMemory(&bufferDesc, sizeof(D3D11_BUFFER_DESC));

        bufferDesc.BindFlags = flag;
        bufferDesc.ByteWidth = (uint)size;
        bufferDesc.CPUAccessFlags = CPUAccessFlag;
        bufferDesc.Usage = (D3D11_USAGE)usage;

        D3D11_SUBRESOURCE_DATA bufferDataDesc;
        ZeroMemory(&bufferDataDesc, sizeof(bufferDataDesc));

        bufferDataDesc.pSysMem = bufferData;

        ID3D11Buffer* handle;

        HRESULT error = device->CreateBuffer(&bufferDesc, &bufferDataDesc, &handle);

        if (FAILED(error))
        {
            return nullptr;
        }

        return handle;
    }

    static ID3D11Buffer* CreateBufferHandle(ID3D11Device* device, D3D11_BIND_FLAG flag, BufferUsage usage, size_t size, uint CPUAccessFlag)
    {
        D3D11_BUFFER_DESC bufferDesc;
        ZeroMemory(&bufferDesc, sizeof(D3D11_BUFFER_DESC));

        bufferDesc.BindFlags = flag;
        bufferDesc.ByteWidth = (uint)size;
        bufferDesc.CPUAccessFlags = CPUAccessFlag;
        bufferDesc.Usage = (D3D11_USAGE)usage;

        ID3D11Buffer* handle;

        HRESULT error = device->CreateBuffer(&bufferDesc, nullptr, &handle);

        if (FAILED(error))
        {
            return nullptr;
        }

        return handle;
    }

    template<>
    VertexBuffer* RenderDevice::CreateBuffer<VertexBuffer>(BufferUsage usage, size_t size, CPUAccess CPUAccess, void* bufferData)
    {
        ID3D11Buffer* handle = CreateBufferHandleWithSubresource(this->device, D3D11_BIND_VERTEX_BUFFER, usage, size, (uint)CPUAccess, bufferData);

        VertexBuffer* buffer = new VertexBuffer(handle);

        stats->AddResource((uintptr_t)handle, "Vertex Buffer");

        return buffer;
    }

    template<>
    IndexBuffer* RenderDevice::CreateBuffer<IndexBuffer>(BufferUsage usage, size_t size, CPUAccess CPUAccess, void* bufferData)
    {
        ID3D11Buffer* handle = CreateBufferHandleWithSubresource(this->device, D3D11_BIND_INDEX_BUFFER, usage, size, (uint)CPUAccess, bufferData);

        IndexBuffer* buffer = new IndexBuffer(handle);

        stats->AddResource((uintptr_t)handle, "Index Buffer");

        return buffer;
    }

    template<>
    ConstantBuffer* RenderDevice::CreateBuffer<ConstantBuffer>(BufferUsage usage, size_t size, CPUAccess CPUAccess, void* bufferData)
    {
        ID3D11Buffer* handle = CreateBufferHandle(this->device, D3D11_BIND_CONSTANT_BUFFER, usage, size, (uint)CPUAccess);

        ConstantBuffer* buffer = new ConstantBuffer(handle);

        stats->AddResource((uintptr_t)handle, "Constant Buffer");

        return buffer;
    }

}
