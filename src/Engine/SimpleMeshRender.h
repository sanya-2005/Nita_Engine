#pragma once
#include "NonCopyable.h"
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

class SimpleMeshRender : public IRender, public NonCopyable
{
private:
	RenderData* data;
	GPU::RenderContext* context;

	GPU::VertexFormat* vertexFormat;

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