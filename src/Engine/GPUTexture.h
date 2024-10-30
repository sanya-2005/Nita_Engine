#pragma once
#include "GPUResource.h"

#include <d3d11.h>

namespace GPU
{
    class Texture2D : public GPUResource
    {
    public:
        Texture2D(void* handle) : GPUResource(handle)
        {

        }
    };
}