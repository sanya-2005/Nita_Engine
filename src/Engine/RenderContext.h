#pragma once
#include "GPUEnums.h"
#include "GPUResource.h"
#include "GPUBuffer.h"
#include "GPUShader.h"
#include "GPUVertexFormat.h"
#include "GPURenderTarget.h"
#include "GPUDepthStencilBuffer.h"

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

		void SetVertexFormat(VertexFormat* vertexFormat);

		void SetVertexBuffer(VertexBuffer& buffer);
		void SetIndexBuffer(IndexBuffer& buffer);
		void SetConstantBuffer(ConstantBuffer& buffer, ConstantBufferTarget target);

		void SetPrimitiveTopology(TopologyType type);

		void SetViewport(D3D11_VIEWPORT& viewport);

		void SetRenderTarget(RenderTargetHandle* renderTarget, DepthStencilBuffer* depthStencil);

        void ClearRenderTarget();
	};
}
