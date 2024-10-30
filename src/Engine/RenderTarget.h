#pragma once
#include "GPURenderTarget.h"
#include "GPUDepthStencilBuffer.h"
#include "GPUTexture.h"
#include "GPUViewport.h"

namespace GPU
{
    struct RenderTargetOptions
    {
        bool useDepthStencil;
    };

    class RenderTarget
    {
    private:
        RenderTargetOptions options;

        RenderTargetHandle* renderTargetHandle;
        DepthStencilBuffer* depthStencil;

    public:
        RenderTarget(RenderTargetHandle& target, DepthStencilBuffer& depthStencilBuffer);
    };
}
