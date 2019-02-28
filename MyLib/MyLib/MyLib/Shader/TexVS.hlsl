#include "Texture.hlsl"

// 頂点シェーダ
[RootSignature(RS)]
Out VS(Input input)
{
    //テクスチャサイズの取得
    float2 size = float2(0.0f, 0.0f);
    tex.GetDimensions(size.x, size.y);

    input.pos    = mul(mtx, input.pos);
    input.pos.xy = float2(-1.0f, 1.0f) + (input.pos.xy / float2((window.x / 2.0f), -(window.y / 2.0f)));
    input.uv     = (((input.uv + reverse) % 2) * uvSize + uvPos) / size;


    Out o;
    o.svpos = input.pos;
    o.pos   = input.pos;
    o.uv    = input.uv;

    return o;
}