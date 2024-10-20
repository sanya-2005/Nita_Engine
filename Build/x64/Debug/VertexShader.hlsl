cbuffer ConstantBuffer : register(b0)
{
    matrix projMat;
    matrix viewMat;
    matrix modelMat;
}

struct VSInput
{
    float3 pos : POSITION;
    float3 color : COLOR;
    float3 norm : NORMAL;
    float2 uv : TEXCOORD;
};

struct VSOutput
{
    float4 color : COLOR;
    float3 norm : NORMAL;
    float2 uv : TEXCOORD;
    float4 pos : SV_POSITION;
};

VSOutput main(VSInput input)
{
    VSOutput output;
    
    matrix mvp = mul(projMat, mul(viewMat, modelMat));
    
    output.pos = mul(mvp, float4(input.pos, 1.0f));
    output.color = float4(input.color, 1.0f);
    output.norm = mul(mvp, float4(input.norm, 1.0f));
    output.uv = input.uv;
    
	return output;
}