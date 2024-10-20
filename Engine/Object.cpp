#include "Object.h"

using namespace DirectX;

Object::Object()
{
	worldMat = XMMatrixIdentity();
	mesh = nullptr;
	isVisible = true;
}

Mesh* Object::GetMesh()
{
	return mesh;
}

void Object::SetMesh(Mesh* mesh)
{
	this->mesh = mesh;
}

XMMATRIX& Object::GetWorldMatrix()
{
	return worldMat;
}

void Object::Move(XMFLOAT3 pos)
{
	worldMat *= XMMatrixTranslation(pos.x, pos.y, pos.z);
}

void Object::Rotate(float angle)
{
	XMVECTOR rotAxis = XMVectorSet(0, 1, 1, 0);
	
	worldMat *= XMMatrixRotationAxis(rotAxis, XMConvertToRadians(angle));
}

void Object::SetVertexBuffer(GPU::VertexBuffer& buffer)
{
	vBuffer = &buffer;
}

void Object::SetIndexBuffer(GPU::IndexBuffer& buffer)
{
	iBuffer = &buffer;
}

void Object::SetVisible(bool visible)
{
	this->isVisible = visible;
}

bool Object::GetVisible()
{
	return isVisible;
}
