#include "Texture.hlsli"

float4 main(Out o) : SV_TARGET
{
	float a = tex.Sample(smp, o.uv).a * alpha;
	if (a <= 0.0f)
	{
		discard;
	}

	
	return float4(tex.Sample(smp, o.uv).xyz, a);
}