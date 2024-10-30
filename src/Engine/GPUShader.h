#pragma once
#include "GPUResource.h"
#include <d3d11.h>
#include <string>

namespace GPU
{
	struct ShaderBytecode
	{
		void* data;
		size_t size;

		/// <summary>
		/// при отчистке ID3DBlob будет отчищен и сегмент памяти с кодом шейдера, поэтому приходится хранить и его
		/// </summary>
		ID3DBlob* shaderBlob;

		~ShaderBytecode()
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

	ShaderBytecode* Compile(ShaderCreateInfo& info);

	class Shader : public GPUResource
	{
	public:
        Shader(void* handle) : GPUResource(handle)
        {
            
        }
	};

	class PixelShader : public Shader
	{
    public:
        PixelShader(void* handle) : Shader(handle)
        {

        }
	};

	class VertexShader : public Shader
	{
    public:
        VertexShader(void* handle) : Shader(handle)
        {

        }
	};
}
