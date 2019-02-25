// ���[�g�V�O�l�`���̒�`
#define RS "RootFlags(ALLOW_INPUT_ASSEMBLER_INPUT_LAYOUT),"\
                    "DescriptorTable(CBV(b0, numDescriptors = 1, space = 0, offset = DESCRIPTOR_RANGE_OFFSET_APPEND), "\
                                    "visibility = SHADER_VISIBILITY_ALL),"\
					"DescriptorTable(CBV(b1, numDescriptors = 1, space = 0, offset = DESCRIPTOR_RANGE_OFFSET_APPEND), "\
                                    "visibility = SHADER_VISIBILITY_ALL),"\
                    "StaticSampler(s0, "\
                                  "filter         = FILTER_MIN_MAG_MIP_LINEAR, "\
                                  "addressU       = TEXTURE_ADDRESS_WRAP, "\
                                  "addressV       = TEXTURE_ADDRESS_WRAP, "\
                                  "addressW       = TEXTURE_ADDRESS_WRAP, "\
                                  "mipLodBias     = 0.0f, "\
                                  "maxAnisotropy  = 0, "\
                                  "comparisonFunc = COMPARISON_NEVER, "\
                                  "borderColor    = STATIC_BORDER_COLOR_TRANSPARENT_BLACK, "\
                                  "minLOD         = 0.0f, "\
                                  "maxLOD         = 3.402823466e+38f, "\
                                  "space          = 0, "\
                                  "visibility     = SHADER_VISIBILITY_ALL)"

SamplerState smp : register(s0);

// ���
cbuffer Info : register(b0)
{
	float4 color;
    float2 window;
}

// WVP
cbuffer WVP : register(b1)
{
    float4x4 world;
    float4x4 view;
    float4x4 projection;
}

// ����
    struct Input
    {
        float4 pos : POSITION;
    };

// �o��
    struct Out
    {
        float4 svpos : SV_POSITION;
        float4 pos : POSITION;
    };

// ���_�V�F�[�_
[RootSignature(RS)]
Out VS(Input input)
{
	input.pos.xy = float2(-1.0f, 1.0f) + (input.pos.xy / float2((window.x / 2.0f), -(window.y / 2.0f)));
   
    input.pos = mul(world, input.pos);
    input.pos = mul(view, input.pos);
    input.pos = mul(projection, input.pos);

    Out o;
    o.pos   = input.pos;
    o.svpos = input.pos;

        return o;
    }

// �s�N�Z���V�F�[�_
float4 PS(Out o) : SV_TARGET
{
    if (color.a <= 0.0f)
    {
		discard;
    }

	return float4(color.rgb, color.a);
}
