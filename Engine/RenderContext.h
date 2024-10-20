#pragma once
#include "GPUEnums.h"
#include "GPUResource.h"
#include "GPUBuffer.h"
#include "GPUShader.h"

#include <d3d11.h>

namespace GPU
{
	class RenderDevice;

	class RenderContext
	{
	private:
		friend class RenderDevice;

		ID3D11DeviceContext* contextHandle;

	public:
		ID3D11DeviceContext* GetContextHandle();

		void SetVertexShader(VertexShader* shader);
		void SePixelShader(PixelShader* shader);

		void SetInputLayout(ID3D11InputLayout* layout);

		void SetVertexBuffer(VertexBuffer& buffer);
		void SetIndexBuffer(IndexBuffer& buffer);
		void SetConstantBuffer(ConstantBuffer& buffer, ConstantBufferTarget target);

		void SetPrimitiveTopology(TopologyType type);

		void SetViewport(D3D11_VIEWPORT& viewport);

		void SetRenderTarget(ID3D11RenderTargetView* renderTarget, ID3D11DepthStencilView* depthStencil);
	};
}
