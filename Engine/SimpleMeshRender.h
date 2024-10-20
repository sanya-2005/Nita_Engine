#pragma once
#include "INonCopyable.h"
#include "IRender.h"
#include "RenderDevice.h"
#include "RenderContext.h"
#include <d3d11.h>

struct SimpleRenderConstantBuffer 
{
	DirectX::XMMATRIX projMat;
    DirectX::XMMATRIX viewMat;
    DirectX::XMMATRIX modelMat;
};

class SimpleMeshRender : public IRender, public INonCopyable
{
private:
	RenderData* data;
	GPU::RenderContext * context;

	ID3D11InputLayout* inputLayout;

	GPU::VertexShader* vertexShader;
	GPU::PixelShader* pixelShader;

	GPU::ConstantBuffer* constantBuffer;

public:
	bool Init(GPU::RenderDevice& device) override;
	void Prepare(GPU::RenderContext& context) override;
	void LoadData(GPU::RenderDevice& device, RenderData& data) override;
	void Render(GPU::RenderDevice& device) override;
	void Destroy() override;
};