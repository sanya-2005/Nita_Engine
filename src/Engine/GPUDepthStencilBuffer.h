#pragma once
#include "GPUResource.h"

namespace GPU
{
    class DepthStencilBuffer : public GPUResource
    {
    public:
        DepthStencilBuffer(void* handle) : GPUResource(handle)
        {

        }
    };
}