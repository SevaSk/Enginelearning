cbuffer cBuf
{
	float4 face_colors[6];
};

float4 main(uint tid : SV_PrimitiveID) : Sv_Target
{
	return face_colors[tid/2 % 6];
}