#include "Effector.h"
#include "../Compute/Compute.h"
#include "Sound.h"
#include <minmax.h>

// ���\�[�X��
#define RSC_MAX 3

// �R���X�g���N�^
Effector::Effector(Sound* sound) : 
	sound(sound)
{
	compute = std::make_unique<Compute>("MyLib/Shader/Effector.hlsl", RSC_MAX);
	param = {};

	Init();
}

// �f�X�g���N�^
Effector::~Effector()
{
}

// ������
void Effector::Init(void)
{
	uint index = 0;
	compute->CBV("param",  sizeof(param), index++);
	compute->UAV("input",  sizeof(float), sound->info.sample * sound->info.channel / sound->Offset(), index++);
	compute->UAV("output", sizeof(float), sound->info.sample * sound->info.channel / sound->Offset(), index++);
}

// ���s
void Effector::Execution(std::vector<float>& input)
{
	//�C��
	sound->distortion = max(sound->distortion, 1.0f);
	sound->comp.ratio = max(sound->comp.ratio, 0.01f);
	sound->comp.ratio = min(sound->comp.ratio, 1.0f);
	sound->volume     = max(sound->volume, 0.0f);
	if (sound->info.channel == 1)
	{
		sound->pan = 0.0f;
	}
	else
	{
		if (sound->pan > 180.0f / sound->info.channel)
		{
			sound->pan = 180.0f / sound->info.channel;
		}
		else if (sound->pan < -180.0f / sound->info.channel)
		{
			sound->pan = -180.0f / sound->info.channel;
		}
	}

	param = { sound->distortion, sound->comp, sound->pan, sound->volume };

	//�R�s�[
	compute->Copy("param",  param);
	compute->Copy("input",  input);
	compute->Copy("output", input);

	//���s
	compute->Execution(uint(input.size()));

	//���f
	compute->UpData("output", input);
}
