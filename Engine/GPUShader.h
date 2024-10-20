#pragma once
#include "GPUResource.h"
#include <d3d11.h>
#include <string>

namespace GPU
{
	struct ShaderByteсode
	{
		void* data;
		size_t size;

		/// <summary>
		/// при отчистке ID3DBlob будет отчищен и сегмент памяти с кодом шейдера, поэтому приходится хранить и его
		/// </summary>
		ID3DBlob* shaderBlob;

		~ShaderByteсode()
		{
			shaderBlob->Release();

			shaderBlob = nullptr;
			data = nullptr;
			size = 0;
		}
	};

	struct ShaderCreateInfo
	{
		std::string entryPoint;
		std::string profile;

		std::wstring path;
	};

	ShaderByteсode* Compile(ShaderCreateInfo& info);

	template<typename T>
	class GPUShader : public GPUResource<T>
	{
	public:

	};

	class PixelShader : public GPUShader<ID3D11PixelShader>
	{

	};

	class VertexShader : public GPUShader<ID3D11VertexShader>
	{

	};
}
