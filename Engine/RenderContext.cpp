#include "RenderContext.h"

namespace GPU
{
	ID3D11DeviceContext* RenderContext::GetContextHandle()
	{
		return contextHandle;
	}

	void RenderContext::SetVertexShader(VertexShader* shader)
	{
		contextHandle->VSSetShader(shader->GetHandle(), nullptr, 0);
	}

	void RenderContext::SePixelShader(PixelShader* shader)
	{
		contextHandle->PSSetShader(shader->GetHandle(), nullptr, 0);
	}

	void RenderContext::SetInputLayout(ID3D11InputLayout* layout)
	{
		contextHandle->IASetInputLayout(layout);
	}

	void RenderContext::SetVertexBuffer(VertexBuffer& buffer)
	{
		ID3D11Buffer* bufferHandle = buffer.GetHandle();
		uint stride = buffer.stride;

		if (stride == 0)
		{
			logger->WriteLine("Vertex Buffer Stride is 0, maybe error?", "GPU", Warning);
		}

		uint offset = buffer.offset;

		contextHandle->IASetVertexBuffers(buffer.slot, 1, &bufferHandle, &stride, &offset);
	}

	void RenderContext::SetIndexBuffer(IndexBuffer& buffer)
	{
		ID3D11Buffer* bufferHandle = buffer.GetHandle();

		if (buffer.format == InvalidFormat)
		{
			logger->WriteLine("Index buffer format is Invalid", "GPU", Error);
		}

		contextHandle->IASetIndexBuffer(bufferHandle, (DXGI_FORMAT)buffer.format, buffer.offset);
	}

	void RenderContext::SetConstantBuffer(ConstantBuffer& buffer, ConstantBufferTarget target)
	{
		ID3D11Buffer* bufferHandle = buffer.GetHandle();

		switch (target)
		{
		case VSTarget:
			contextHandle->VSSetConstantBuffers(buffer.slot, 1, &bufferHandle);
			break;
		case PSTarget:
			contextHandle->PSSetConstantBuffers(buffer.slot, 1, &bufferHandle);
			break;
		}
	}

	void RenderContext::SetPrimitiveTopology(TopologyType type)
	{
		contextHandle->IASetPrimitiveTopology((D3D11_PRIMITIVE_TOPOLOGY)type);
	}

	void RenderContext::SetViewport(D3D11_VIEWPORT& viewport)
	{
		contextHandle->RSSetViewports(1, &viewport);
	}

	void RenderContext::SetRenderTarget(ID3D11RenderTargetView* renderTarget, ID3D11DepthStencilView* depthStencil)
	{
		contextHandle->OMSetRenderTargets(1, &renderTarget, depthStencil);
	}
}
