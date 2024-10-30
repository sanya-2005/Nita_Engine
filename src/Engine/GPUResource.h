#pragma once
#include "GPUResourceStatistic.h"
#include "Log.h"

namespace GPU
{
	class GPUResource
	{
	private:
		void* handle;

	public:

        GPUResource(void* handle)
        {
            this->handle = handle;
        }

		inline void* GetHandle()
		{
			return handle;
		}

		virtual ~GPUResource();
	};
}
