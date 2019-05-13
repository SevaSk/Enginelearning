float4 main(float3 color : Color) : Sv_Target
{
	return float4(color,1.0f);
}