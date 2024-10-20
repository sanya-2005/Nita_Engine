#pragma once
#include "D3D11Utils.h"
#include "Log.h"

namespace GPU
{
	template<typename T>
	class GPUResource
	{
	private:
		T* handle;

	public:
		void Destroy()
		{
			D3D11Utils::SafeRelease<T>(handle);
			handle = nullptr;
		}

		inline T* GetHandle()
		{
			return handle;
		}

		inline void SetHandle(T* handle)
		{
			this->handle = handle;
		}

		virtual ~GPUResource()
		{
			if (handle != nullptr)
			{
				logger->WriteLine("Error: unreleased GPU resource", "GPU");
			}
		}
	};
}
