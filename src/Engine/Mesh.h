#pragma once
#include "EngineCore\Types.h"

#include <vector>
#include <DirectXMath.h>

struct Vertex
{
    DirectX::XMFLOAT3 position;
    DirectX::XMFLOAT3 color;
    DirectX::XMFLOAT3 normal;
    DirectX::XMFLOAT2 uv;
};

class Mesh
{
private:
    std::vector<Vertex> vertices;

    std::vector<unsigned short> indices;

public:
    Mesh(std::vector<Vertex>&& vertices);
    Mesh(Mesh& copy);
    Mesh(Mesh&& copy);

    void AddVertex(Vertex& vertex);
    void AddVertices(Vertex* vertices, uint verticesCount);

    void AddIndex(unsigned short index);
    void AddIndices(unsigned short* indices, uint indicesCount);
    void AddIndices(std::vector<unsigned short>&& indices);

    std::vector<Vertex>& GetVertices();
    std::vector<unsigned short>& GetIndices();

    uint VerticesCount() 
    {
        return (uint)vertices.size();
    }

    uint IndicesCount()
    {
        return (uint)indices.size();
    }
};