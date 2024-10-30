#pragma once
#include "GPUBuffer.h"

class RenderVisual
{
private:
    GPU::VertexBuffer* VB;
    GPU::IndexBuffer* IB;

public:
    void SetVertexBuffer(GPU::VertexBuffer* buffer)
    {
        VB = buffer;
    }

    void SetIndexBuffer(GPU::IndexBuffer* buffer)
    {
        IB = buffer;
    }

    GPU::VertexBuffer* GetVertexBuffer()
    {
        return VB;
    }

    GPU::IndexBuffer* GetIndexBuffer()
    {
        return IB;
    }

    virtual ~RenderVisual()
    {
        delete VB;

        delete IB;
    }
};