#include "SimpleMeshRender.h"
#include "D3D11Utils.h"
#include "Log.h"
#include "Object.h"
#include "Level.h"

using namespace DirectX;
using namespace D3DUtils;
using namespace GPU;

#include <string>
#include <d3d11.h>

bool SimpleMeshRender::Init(GPU::RenderDevice& device)
{
    std::string logTitle = "Simple Mesh Render";

    logger->WriteLine("Init Simple Mesh Render", logTitle);

    constantBuffer = device.CreateBuffer<ConstantBuffer>(DefaultUsage, sizeof(XMMATRIX) * 3, NoAccess, nullptr);

    if (!constantBuffer)
    {
        logger->WriteLine("error creating constant buffer", logTitle);
        return false;
    }

    ShaderCreateInfo info;

    info.entryPoint = "main";
    info.profile = "vs_5_0";
    info.path = L"VertexShader.hlsl";

    ShaderBytecode* vs_code = Compile(info);

    if (!vs_code)
    {
        logger->WriteLine("Error compiling Vertex Shader", logTitle);
        return false;
    }

    vertexShader = device.CreateShader<VertexShader>(*vs_code);

    if (!vertexShader)
    {
        logger->WriteLine("Error create Vertex Shader", logTitle);
        return false;
    }

    VertexAttribute attributes[] = {
        {"POSITION", 0, Vec3_float, 0, 0, PerVertex, 0},
        { "COLOR", 0, Vec3_float, 0, 12, PerVertex, 0 },
        { "NORMAL", 0, Vec3_float, 0, 24, PerVertex, 0 },
        {"TEXCOORD", 0, Vec2_float, 0, 36, PerVertex, 0}
    };
    
    vertexFormat = device.CreateVertexFormat(attributes, 4, *vs_code);

    if (!vertexFormat)
    {
        logger->WriteLine("Error create Input Layout", logTitle);

        return false;
    }

    delete vs_code;

    info.profile = "ps_5_0";
    info.path = L"PixelShader.hlsl";

    ShaderBytecode* ps_code = Compile(info);

    if (!ps_code)
    {
        logger->WriteLine("Error compiling Pixel Shader", logTitle);
        return false;
    }

    pixelShader = device.CreateShader<PixelShader>(*ps_code);

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

    context.SetVertexFormat(vertexFormat);
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
                                                                    NoAccess, mesh->GetVertices().data());
            vBuff->stride = sizeof(Vertex);

            obj->SetVertexBuffer(vBuff);
        }

        if (obj->GetIndexBuffer() == nullptr)
        {
            Mesh* mesh = obj->GetMesh();

            IndexBuffer* iBuff = device.CreateBuffer<IndexBuffer>(DefaultUsage, mesh->IndicesCount() * sizeof(WORD),
                                                                  NoAccess, mesh->GetIndices().data());
            iBuff->format = UShort;

            obj->SetIndexBuffer(iBuff);
        }
    }
}

void SimpleMeshRender::Render(GPU::RenderDevice& device)
{
    for (Object* obj : data->level->GetObjectsList())
    {
        if (obj->IsVisible())
        {
            context->SetVertexBuffer(*obj->GetVertexBuffer());
            context->SetIndexBuffer(*obj->GetIndexBuffer());

            SimpleRenderConstantBuffer subRes{};

            subRes.projMat = data->projectionMatrix;
            subRes.viewMat = data->viewMatrix;
            subRes.modelMat = obj->GetWorldMatrix();

            device.UpdateSubResource(*constantBuffer, &subRes);

            device.DrawIndexed(obj->GetMesh()->IndicesCount());
        }
    }
}

void SimpleMeshRender::Destroy()
{
    delete constantBuffer;
    delete pixelShader;
    delete vertexFormat;
    delete vertexShader;
}
