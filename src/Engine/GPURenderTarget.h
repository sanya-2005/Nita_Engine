#pragma once
#include "GPUResource.h"

namespace GPU
{
    class RenderTargetHandle : public GPUResource
    {
    public:
        RenderTargetHandle(void* handle) : GPUResource(handle)
        {

        }
    };
}
