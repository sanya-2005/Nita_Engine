struct PSInput
{
    float4 color : COLOR;
    float3 norm : NORMAL;
    float2 uv : TEXCOORD;
};

float4 main(PSInput input) : SV_TARGET
{
    float3 light_dir = float3(1.0f, 0.74f, 0.5f);
    
    float col = dot(input.norm, light_dir);
    return saturate(float4(col * input.uv, 0.0f, 1.0f));
}