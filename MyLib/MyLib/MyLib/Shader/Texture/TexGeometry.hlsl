#include "Texture.hlsli"
#include "../Shader.hlsli"

#define MAX_VERTEX 4

[maxvertexcount(MAX_VERTEX)]
void main(lineadj Out input[MAX_VERTEX], inout TriangleStream<Out> stream)
{
	stream.RestartStrip();

	//’†SÀ•W
    float3 center = 0.0f;

	uint low = MAX_VERTEX / 2;
	Out output[MAX_VERTEX];

    uint i = 0;
    for (i = 0; i < low; ++i)
	{
		output[i]         = input[i];
        center += output[i].pos.xyz;
        output[low + i] = input[low + i];
        center += output[low + i].pos.xyz;

        output[i].uv       = ((input[i].uv * !reverse) + (input[low + i].uv * reverse)) / size;
        output[low + i].uv = ((input[low + i].uv * !reverse) + (input[i].uv * reverse)) / size;
    }

    center /= MAX_VERTEX;
    for (i = 0; i < MAX_VERTEX; ++i)
    {
        output[i].svpos = mul(Translate(-center), output[i].svpos);
        output[i].svpos = mul(RotateZ(angle), output[i].svpos);
        output[i].svpos = mul(Translate(center), output[i].svpos);

        stream.Append(output[i]);
    }
}
