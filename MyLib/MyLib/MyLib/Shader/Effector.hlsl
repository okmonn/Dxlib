// ���[�g�V�O�l�`���̐錾
#define RS "RootFlags(ALLOW_INPUT_ASSEMBLER_INPUT_LAYOUT),"\
					"DescriptorTable(CBV(b0, numDescriptors = 1, space = 0, offset = DESCRIPTOR_RANGE_OFFSET_APPEND), "\
                                    "visibility = SHADER_VISIBILITY_ALL),"\
					"DescriptorTable(CBV(b1, numDescriptors = 1, space = 0, offset = DESCRIPTOR_RANGE_OFFSET_APPEND), "\
                                    "visibility = SHADER_VISIBILITY_ALL),"\
                    "DescriptorTable(UAV(u0, numDescriptors = 1, space = 0, offset = DESCRIPTOR_RANGE_OFFSET_APPEND), "\
                                    "visibility = SHADER_VISIBILITY_ALL),"\
                    "DescriptorTable(UAV(u1, numDescriptors = 1, space = 0, offset = DESCRIPTOR_RANGE_OFFSET_APPEND), "\
                                    "visibility = SHADER_VISIBILITY_ALL),"\
                    "StaticSampler(s0, "\
                                  "filter = FILTER_MIN_MAG_MIP_LINEAR, "\
                                  "addressU = TEXTURE_ADDRESS_WRAP, "\
                                  "addressV = TEXTURE_ADDRESS_WRAP, "\
                                  "addressW = TEXTURE_ADDRESS_WRAP, "\
                                  "mipLodBias = 0.0f, "\
                                  "maxAnisotropy = 0, "\
                                  "comparisonFunc = COMPARISON_NEVER, "\
                                  "borderColor = STATIC_BORDER_COLOR_TRANSPARENT_BLACK, "\
                                  "minLOD = 0.0f, "\
                                  "maxLOD = 3.402823466e+38f, "\
                                  "space = 0, "\
                                  "visibility = SHADER_VISIBILITY_ALL)"

// �K���O�f�[�^
RWStructuredBuffer<float> input  : register(u0);
// �K���f�[�^
RWStructuredBuffer<float> output : register(u1);

// �~����
#define PI 3.14159265358979323846f

// �p�����[�^
cbuffer Info : register(b0)
{
	//�T���v�����O���g��
    uint sample;
	//�ʎq���r�b�g��
    uint bit;
	//�`�����l����
    uint channel;
}

// �p�����[�^
cbuffer Param : register(b1)
{
	//臒l
    float threshold;
	//���V�I
    float ratio;
	//�f�B�X�g�[�V����
	float distortion;
	//�ϒ��[�x
    float depth;
	//�ϒ����g��
    float rate;
	//�ǂݍ��݃C���f�b�N�X
    float index;
    //�p��
    float pan;
	//����
	float volume;
};

// �R���v���b�T
void Compressor(uint id)
{
	//������
	float gain = 1.0f / (threshold + (1.0f - threshold) * ratio);

	//���k
	if (output[id] > threshold)
	{
		output[id] = threshold + (output[id] - threshold) * ratio;
	}
	else if (output[id] < -threshold)
	{
		output[id] = -threshold + (input[id] + threshold) * ratio;
	}

	//����
	output[id] *= gain;
}

// �f�B�X�g�[�V����(�n�[�h�N���b�s���O)
void Distortion(uint id)
{
	output[id] *= distortion;
	if (output[id] > 1.0f)
	{
		output[id] = 1.0f;
	}
	else if (output[id] < -1.0f)
	{
		output[id] = -1.0f;
	}
}

// �g������
void Tremor(uint id)
{
    //�ϒ��M��
    float signal = 1.0f + depth * sin(2.0f * PI * rate * (index + id) / sample);

    output[id] *= signal;
}

// �p���j���O
void Panning(uint id)
{
    float tmp = pan / 90.0f;

    if (id % channel == 0)
    {
        //��
        output[id] *= 1.0f - tmp;
    }
    else
    {
        //�E
        output[id] *= 1.0f + tmp;
    }
}

// ���ʒ���
void Volume(uint id)
{
    output[id] *= volume;
}

[RootSignature(RS)]
[numthreads(1, 1, 1)]
void CS(uint3 gID : SV_GroupID, uint3 gtID : SV_GroupThreadID, uint3 disID : SV_DispatchThreadID)
{
    output[gID.x] = input[gID.x];

    Compressor(gID.x);
    Distortion(gID.x);
    Tremor(gID.x);
    Panning(gID.x);
    Volume(gID.x);

    AllMemoryBarrierWithGroupSync();
}