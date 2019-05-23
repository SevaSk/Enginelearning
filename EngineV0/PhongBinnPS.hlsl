
static const float3 lightpos = { 0.0f, 0.0f, 1.0f };
static const float3 ambient = { 0.15f, 0.15f, 0.15f };
static const float3 diffuseColor = { 1.0f, 1.0f, 1.0f };
static const float diffuseIntensity = 1.0f;
static const float attConst = 1.0f;
static const float attLin = 1.0f;
static const float attQuad = 1.0f;


float4 main(float3 worldPos : Position, float3 n : Normal) : SV_Target
{
    const float3 vToL = lightpos - worldPos;
    const float distToL = length(vToL);
    const float3 dirToL = vToL / distToL;

    const float3 att = attConst + attLin * distToL + attQuad * (distToL * distToL);

    const float3 diffuse = diffuseColor * diffuseIntensity * att * max(0.0f, dot(dirToL, n));

    return float4(saturate(diffuse + ambient), 1.0f);
    
}