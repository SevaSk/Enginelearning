static const float3 materialColor = { 0.5f,0.5f,0.5f };
static const float3 lightpos = { 0.0f, 30.0f, 0.0f };
static const float3 ambient = { 1.00f, 1.00f, 1.00f };
static const float3 diffuseColor = { 1.0f, 1.0f, 1.0f };
static const float diffuseIntensity = 5000.0f;
static const float attConst = 5.0f;
static const float attLin = 0.045f;
static const float attQuad = 0.0075f;

float4 main(float3 worldPos : Position, float3 n : Normal) : SV_Target
{
    const float3 vToL = lightpos - worldPos;
    const float distToL = length(vToL);
    const float3 dirToL = vToL / distToL;

    const float3 att = 1.0f/(attConst + attLin * distToL + attQuad * (distToL * distToL));

    const float3 diffuse = diffuseColor * diffuseIntensity * att * max(0.0f, dot(dirToL, n));

    return float4(saturate(diffuse + ambient) * materialColor, 1.0f);
    
}