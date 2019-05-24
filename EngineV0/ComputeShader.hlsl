
struct Pos
{
	float3 pos;
};

StructuredBuffer<Pos> Buffer0 : register(t0);

[numthreads(1, 1, 1)]
void CSMain( uint3 DTid : SV_DispatchThreadID )
{

}