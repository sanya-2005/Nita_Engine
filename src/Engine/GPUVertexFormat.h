#pragma once
#include "GPUResource.h"
#include "GPUEnums.h"

#include <d3d11.h>
#include <string>

namespace GPU
{
	struct VertexAttribute
	{
		std::string name;

		uint semanticIndex;
		GPUFormat format;

		uint slot;
		uint offset;

		PerVertexElementMode elementMode;
		uint instanceStep;

        D3D11_INPUT_ELEMENT_DESC ConvertToD3dInputElement();
	};

    class VertexFormat : public GPUResource
    {
    public:
        VertexFormat(void* handle) : GPUResource(handle)
        {

        }
    };
}