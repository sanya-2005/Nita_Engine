#pragma once
#include "OSWindow.h"
#include "IRender.h"
#include "INonCopyable.h"

#include <d3d11.h>

/// <summary>
/// Главный модуль рендеринга
/// </summary>
class RenderEngine : public INonCopyable
{
private:
	OSWindow* osWindow;

	GPU::RenderDevice* device;
	GPU::RenderContext* context;

	ID3D11RenderTargetView* renderTargetView;
	D3D11_VIEWPORT* viewport;

	ID3D11DepthStencilView* depthStencilView;
	GPU::GPUTexture2D* depthStencilBuffer;

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