#pragma once
#include"utils.h"

#include <d3d11.h>

namespace D3D11Utils
{
	template<typename T>
	void SafeRelease(T* resource)
	{
		if (resource != nullptr)
		{
			resource->Release();
		}
	}
}
