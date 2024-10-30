#include "GPUResource.h"
#include "D3D11Utils.h"

namespace GPU
{
    GPUResource::~GPUResource()
    {
        stats->RemoveResource((uintptr_t)handle);

        D3DUtils::SafeRelease((ID3D11Resource*)handle);
        handle = nullptr;
    }
}
