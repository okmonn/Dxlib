#include "Primitive.hlsl"

// �s�N�Z���V�F�[�_
float4 PS(Out o) : SV_TARGET
{
    if (color.a <= 0.0f)
    {
        discard;
    }

    return float4(color);
}

