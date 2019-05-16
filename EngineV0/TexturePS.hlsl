Texture2D tex;

SamplerState splr;

float4 main(float tc: TexCoord ) : SV_Target
{
	return tex.Sample(splr,tc);
}