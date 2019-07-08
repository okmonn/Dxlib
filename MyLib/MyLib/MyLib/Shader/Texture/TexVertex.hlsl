#include "Texture.hlsli"

[RootSignature(RS)]
Out main(Input input)
{
	input.pos.xy = float2(-1.0f, 1.0f) + (input.pos.xy / float2((winSize.x / 2.0f), -(winSize.y / 2.0f)));

	Out o;
	o.svpos = input.pos;
	o.pos   = input.pos;
	o.uv    = input.uv;

	return o;
}