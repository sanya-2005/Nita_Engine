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
};

struct VSOutput
{
    float4 color : COLOR;
    float4 pos : SV_POSITION;
};

VSOutput main(VSInput input)
{
    VSOutput output;
    matrix mvp = mul(projMat, mul(viewMat, modelMat));
    output.pos = mul(mvp, float4(input.pos, 1.0f));
    output.color = float4(input.color, 1.0f);
	return output;
}