cbuffer CBuf
{
    matrix model;
    matrix modelViewProj;
};

struct BufferStruct
{
    float3 pos;
    float3 normal;
    float3 color;
};

StructuredBuffer<BufferStruct> InBuff;

struct VSOut
{
    float3 worldPos : Position;
    float3 normal : Normal;
    float3 color : Color;
    float4 pos : SV_Position;
};

VSOut main(uint id : SV_VertexID)
{
    VSOut vso;
    vso.worldPos = (float3) mul(float4( InBuff[id].pos, 1.0f), model);
    vso.normal = mul(InBuff[id].normal, (float3x3) model);
    vso.pos = mul(float4(InBuff[id].pos, 1.0f), modelViewProj);
    vso.color = InBuff[id].color;
    return vso;
}