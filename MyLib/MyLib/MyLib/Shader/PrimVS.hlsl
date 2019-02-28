#include "Primitive.hlsl"

// 頂点シェーダ
[RootSignature(RS)]
Out VS(Input input)
{
    input.pos.xy = float2(-1.0f, 1.0f) + (input.pos.xy / float2((window.x / 2.0f), -(window.y / 2.0f)));
   
    Out o;
    o.pos   = input.pos;
    o.svpos = input.pos;

    return o;
}