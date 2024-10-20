#pragma once
#include "Mesh.h"
#include "GPUBuffer.h"

#include <DirectXMath.h>

class Object
{
private:
	DirectX::XMMATRIX worldMat;

	Mesh* mesh;

	GPU::VertexBuffer* vBuffer;
	GPU::IndexBuffer* iBuffer;

	bool isVisible;

public:
	Object();

	Mesh* GetMesh();
	void SetMesh(Mesh* mesh);

    DirectX::XMMATRIX& GetWorldMatrix();

	void Move(DirectX::XMFLOAT3 pos);
	void Rotate(float angle);

	void SetVertexBuffer(GPU::VertexBuffer& buffer);
	void SetIndexBuffer(GPU::IndexBuffer& buffer);

	void SetVisible(bool visible);
	bool GetVisible();

	GPU::VertexBuffer* GetVertexBuffer()
	{
		return vBuffer;
	}

	GPU::IndexBuffer* GetIndexBuffer()
	{
		return iBuffer;
	}
};