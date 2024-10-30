#pragma once
#include <d3d11.h>

namespace D3DUtils
{
    template<typename T>
    concept IsReleasable = std::convertible_to<T*, IUnknown*>;

	template<typename T> requires IsReleasable<T>
	void SafeRelease(T* resource)
	{
		if (resource != nullptr)
		{
			resource->Release();
		}
	}
}
