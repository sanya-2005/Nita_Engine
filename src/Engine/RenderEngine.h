#pragma once
#include "OSWindow.h"
#include "IRender.h"
#include "NonCopyable.h"

#include <d3d11.h>


class RenderEngine : public NonCopyable
{
private:
	OSWindow* osWindow;

	GPU::RenderDevice* device;
	GPU::RenderContext* context;

	GPU::RenderTargetHandle* outputRenderTarget;
	D3D11_VIEWPORT* viewport;

	GPU::DepthStencilBuffer* depthStencilView;
	GPU::Texture2D* depthStencilBuffer;

	ID3D11DepthStencilState* depthStencilState;

	IRender* firstRender;

public:
	RenderData* data;

	bool Init(OSWindow& osWindow);
	void Update();
	void Render();

	void Clear(Color& clearColor);

	void Resize(uint newWitdh, uint newHeight);
	void Resize(Size& size);

	void Destroy();
};