#pragma once
#include "GPUResource.h"
#include "GPUEnums.h"

#include <d3d11.h>
#include <string>
#include <vector>

namespace GPU
{
	struct VertexFormat
	{
		std::string name;

		uint semanticIndex;
		GPUFormat format;

		uint slot;
		uint offset;

		PerVertexElementMode elementMode;
		uint instanceStep;
	};

	class GPUVertexFormat : public GPUResource<ID3D11InputLayout>
	{

	};
}