#pragma once
#include "utils.h"
#include "GPUEnums.h"
#include "GPUResource.h"

#include <d3d11.h>

namespace GPU
{
	class GPUBuffer : public GPUResource<ID3D11Buffer>
	{

	};

	class VertexBuffer : public GPUBuffer
	{
	public:
		uint slot;
		uint stride;
		uint offset;

		VertexBuffer() : slot(0), stride(0), offset(0)
		{

		}
	};

	class IndexBuffer : public GPUBuffer
	{
	public:
		GPUFormat format;
		uint offset;

		IndexBuffer() : format((GPUFormat)1488), offset(0)
		{

		}
	};

	class ConstantBuffer : public GPUBuffer
	{
	public:
		uint slot;
	};
}
