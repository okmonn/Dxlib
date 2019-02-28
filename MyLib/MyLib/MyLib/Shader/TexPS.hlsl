#include "Texture.hlsl"

// ピクセルシェーダ
float4 PS(Out o) : SV_TARGET
{
    float a = tex.Sample(smp, o.uv).a * color.a;
    if (a <= 0.0f)
    {
        discard;
    }

    return float4(tex.Sample(smp, o.uv).xyz, a);
}