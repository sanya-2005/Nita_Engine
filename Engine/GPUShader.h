#pragma once
#include "GPUResource.h"
#include <d3d11.h>
#include <string>

namespace GPU
{
	struct ShaderByte�ode
	{
		void* data;
		size_t size;

		/// <summary>
		/// ��� �������� ID3DBlob ����� ������� � ������� ������ � ����� �������, ������� ���������� ������� � ���
		/// </summary>
		ID3DBlob* shaderBlob;

		~ShaderByte�ode()
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

	ShaderByte�ode* Compile(ShaderCreateInfo& info);

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
