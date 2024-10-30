#pragma once
#include "EngineCore/Types.h"
#include "GPUEnums.h"
#include "GPUResource.h"

#include <d3d11.h>

namespace GPU
{
	class GPUBuffer : public GPUResource
	{
    public:
        GPUBuffer(void* handle) : GPUResource(handle)
        {

        }
	};

	class VertexBuffer : public GPUBuffer
	{
	public:
		uint slot;
		uint stride;
		uint offset;
        uint count;

		VertexBuffer(void* handle) : GPUBuffer(handle),
        slot(0), stride(0), offset(0), count(0)
		{

		}
	};

	class IndexBuffer : public GPUBuffer
	{
	public:
		GPUFormat format;
		uint offset;
        uint count;

		IndexBuffer(void* handle) : GPUBuffer(handle), format((GPUFormat)1488), offset(0), count(0)
		{

		}
	};

	class ConstantBuffer : public GPUBuffer
	{
	public:
		uint slot;

        ConstantBuffer(void* handle) : GPUBuffer(handle), slot(0)
        {

        }
	};
}
