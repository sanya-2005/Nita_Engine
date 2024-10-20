#pragma once
#include "GPUResource.h"

#include <d3d11.h>

namespace GPU
{
	class GPUTexture2D : public GPUResource<ID3D11Texture2D>
	{

	};
}