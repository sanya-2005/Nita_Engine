#pragma once
#include "Mesh.h"
#include "RenderVisual.h"

#include <DirectXMath.h>

class Object : public RenderVisual
{
private:
	DirectX::XMMATRIX worldMat;

	Mesh* mesh;

	bool isVisible;

public:
	Object();

	Mesh* GetMesh();
	void SetMesh(Mesh* mesh);

    DirectX::XMMATRIX& GetWorldMatrix();

	void Move(DirectX::XMFLOAT3 pos);
	void Rotate(float angle);

	void SetVisible(bool visible);
	bool IsVisible();

    void Destroy();
};