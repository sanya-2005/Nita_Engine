#include "Mesh.h"

Mesh::Mesh(std::vector<Vertex>&& vertices)
{
	this->vertices = std::vector<Vertex>(vertices);
}

Mesh::Mesh(Mesh& copy)
{
	this->vertices = std::vector<Vertex>(copy.vertices);
	this->indices = std::vector<unsigned short>(copy.indices);
}

Mesh::Mesh(Mesh&& copy)
{
	this->vertices = std::vector<Vertex>(copy.vertices);
	this->indices = std::vector<unsigned short>(copy.indices);
}

void Mesh::AddVertex(Vertex& vertex)
{
	vertices.push_back(vertex);
}

void Mesh::AddVertices(Vertex* vertices, uint verticesCount)
{
	this->vertices = std::vector<Vertex>(vertices, vertices+verticesCount);
}

void Mesh::AddIndex(unsigned short index)
{
	indices.push_back(index);
}

void Mesh::AddIndices(unsigned short* indices, uint indicesCount)
{
	this->indices = std::vector<unsigned short>(indices, indices + indicesCount);
}

void Mesh::AddIndices(std::vector<unsigned short>&& indices)
{
	this->indices = std::vector<unsigned short>(indices);
}

std::vector<Vertex>& Mesh::GetVertices()
{
	return vertices;
}

std::vector<unsigned short>& Mesh::GetIndices()
{
	return indices;
}
