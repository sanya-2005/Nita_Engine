#include "SimpleMeshRender.h"
#include "D3D11Utils.h"
#include "Log.h"
#include "Object.h"
#include "Level.h"

using namespace DirectX;
using namespace D3D11Utils;
using namespace GPU;

#include <string>
#include <exception>
#include <d3d11.h>
#include <d3dcompiler.h>

bool SimpleMeshRender::Init(GPU::RenderDevice& device)
{
    std::string logTitle = "Simple Mesh Render";

    logger->WriteLine("Init Simple Mesh Render", logTitle);

    constantBuffer = device.CreateBuffer<ConstantBuffer>(DefaultUsage, sizeof(XMMATRIX) * 3, 0, nullptr);
    constantBuffer->slot = 0;

    if (!constantBuffer)
    {
        logger->WriteLine("error creating constant buffer", logTitle);
        return false;
    }

    ShaderCreateInfo info;

    info.entryPoint = "main";
    info.profile = "vs_5_0";
    info.path = L"VertexShader.hlsl";

    ShaderByteñode* vs_code = Compile(info);

    if (!vs_code)
    {
        logger->WriteLine("Error compiling Vertex Shader", logTitle);
        return false;
    }

    vertexShader = device.CreateShader<VertexShader>(*vs_code, nullptr);

    if (!vertexShader)
    {
        logger->WriteLine("Error create Vertex Shader", logTitle);
        return false;
    }

    D3D11_INPUT_ELEMENT_DESC layoutDesc[] = 
    {
        {"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0},
        { "COLOR", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 },
        { "NORMAL", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 24, D3D11_INPUT_PER_VERTEX_DATA, 0 },
        {"TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 36, D3D11_INPUT_PER_VERTEX_DATA, 0}
    };
    
    inputLayout = device.CreateInputLayout(layoutDesc, 4, *vs_code);

    if (!inputLayout)
    {
        logger->WriteLine("Error create Input Layout", logTitle);

        return false;
    }

    delete vs_code;

    info.profile = "ps_5_0";
    info.path = L"PixelShader.hlsl";

    ShaderByteñode* ps_code = Compile(info);

    if (!ps_code)
    {
        logger->WriteLine("Error compiling Pixel Shader", logTitle);
        return false;
    }

    pixelShader = device.CreateShader<PixelShader>(*ps_code, nullptr);

    delete ps_code;

    if (!pixelShader)
    {
        logger->WriteLine("Error create Pixel Shader", logTitle);

        return false;
    }

    return true;
}

void SimpleMeshRender::Prepare(GPU::RenderContext& context)
{
    this->context = &context;

    context.SetInputLayout(inputLayout);
    context.SetConstantBuffer(*constantBuffer, VSTarget);

    context.SetPrimitiveTopology(TriangleList);

    context.SetVertexShader(vertexShader);
    context.SePixelShader(pixelShader);
}

void SimpleMeshRender::LoadData(GPU::RenderDevice& device, RenderData& data)
{
    this->data = &data;

    for (Object* obj : data.level->GetObjectsList())
    {
        if (obj->GetVertexBuffer() == nullptr)
        {
            Mesh* mesh = obj->GetMesh();

            VertexBuffer* vBuff = device.CreateBuffer<VertexBuffer>(DefaultUsage, mesh->VerticesCount() * sizeof(Vertex),
                                                                    0, mesh->GetVertices().data());
            vBuff->stride = sizeof(Vertex);

            obj->SetVertexBuffer(*vBuff);
        }

        if (obj->GetIndexBuffer() == nullptr)
        {
            Mesh* mesh = obj->GetMesh();

            IndexBuffer* iBuff = device.CreateBuffer<IndexBuffer>(DefaultUsage, mesh->IndicesCount() * sizeof(WORD),
                                                                  0, mesh->GetIndices().data());
            iBuff->format = UShort;

            obj->SetIndexBuffer(*iBuff);
        }
    }
}

void SimpleMeshRender::Render(GPU::RenderDevice& device)
{
    for (Object* obj : data->level->GetObjectsList())
    {
        if (obj->GetVisible())
        {
            context->SetVertexBuffer(*obj->GetVertexBuffer());
            context->SetIndexBuffer(*obj->GetIndexBuffer());

            SimpleRenderConstantBuffer subRes{};

            subRes.projMat = data->projectionMatrix;
            subRes.viewMat = data->viewMatrix;
            subRes.modelMat = obj->GetWorldMatrix();

            device.UpdateSubResource<ID3D11Buffer>(*constantBuffer, &subRes);

            device.DrawIndexed(obj->GetMesh()->IndicesCount());
        }
    }
}

void SimpleMeshRender::Destroy()
{
    SafeRelease(inputLayout);
    constantBuffer->Destroy();
    vertexShader->Destroy();
    pixelShader->Destroy();
}
