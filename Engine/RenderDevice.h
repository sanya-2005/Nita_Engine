#pragma once
#include "RenderContext.h"
#include "utils.h"
#include "GPUEnums.h"
#include "GPUBuffer.h"
#include "GPUTexture.h"
#include "GPUShader.h"

#include <d3d11.h>

class OSWindow;

namespace GPU
{
	class RenderDevice
	{
	private:
		ID3D11Device* device;
		IDXGISwapChain* swapChain;
		RenderContext* context;

	public:
		/// <summary>
		/// Временное решение, пока не будет полностью реализован GPU-интерфейс
		/// </summary>
		/// <returns></returns>
		ID3D11Device* GetDeviceHandle() 
		{
			return device; 
		}

		bool Init(OSWindow& osWindow, RenderContext& context);

		ID3D11RenderTargetView* CreateRenderTarget(GPUTexture2D* texture);
		ID3D11DepthStencilView* CreateDepthStencil(GPUTexture2D* texture);

		GPUTexture2D* GetBackBuffer();

		GPUTexture2D* CreateTexture2D(TextureBindMode mode, Size size, GPUFormat format);

		template<typename T>
		T* CreateShader(ShaderByteсode& code, ID3D11ClassLinkage* classLinkage);

		template<typename T>
		T* CreateBuffer(BufferUsage usage, size_t size, uint CPUAccessFlag, void* bufferData);

		ID3D11InputLayout* CreateInputLayout(D3D11_INPUT_ELEMENT_DESC* decsArray, uint decsSize, ShaderByteсode& code);

		template<typename T>
		void UpdateSubResource(GPUResource<T>& resource, void* data)
		{
			ID3D11DeviceContext* handle = context->GetContextHandle();
			handle->UpdateSubresource(resource.GetHandle(), 0, nullptr, data, 0, 0);
		}

		void SwapBuffers();

		void Resize(uint width, uint height);

		void Flush();
		void DrawIndexed(uint count);
	};
}
