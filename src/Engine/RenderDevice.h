#pragma once
#include "RenderContext.h"
#include "EngineCore/Types.h"
#include "GPUEnums.h"
#include "GPUBuffer.h"
#include "GPUTexture.h"
#include "GPUShader.h"
#include "GPUVertexFormat.h"
#include "GPURenderTarget.h"
#include "GPUDepthStencilBuffer.h"

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
		ID3D11Device* GetDeviceHandle() 
		{
			return device; 
		}

		bool Init(OSWindow& osWindow, RenderContext& context);

		RenderTargetHandle* CreateRenderTarget(Texture2D* texture);
		DepthStencilBuffer* CreateDepthStencil(Texture2D* texture);

		Texture2D* GetBackBuffer();

		Texture2D* CreateTexture2D(TextureBindMode mode, Size size, GPUFormat format);

		template<typename T>
		T* CreateShader(ShaderBytecode& code);

		template<typename T>
		T* CreateBuffer(BufferUsage usage, size_t size, CPUAccess CPUAccess, void* bufferData);

        VertexFormat* CreateVertexFormat(VertexAttribute* attributesArray, uint arraySize, ShaderBytecode& code);

		void UpdateSubResource(GPUResource& resource, void* data);

		void SwapBuffers();

		void Resize(uint width, uint height);

		void Flush();
		void DrawIndexed(uint count);
	};
}
