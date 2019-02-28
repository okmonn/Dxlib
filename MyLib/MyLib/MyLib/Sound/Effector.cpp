#include "Effector.h"
#include "Sound.h"
#include "../Compute/Compute.h"
#include "../etc/Func.h"
#include <minmax.h>

// ���\�[�X��
#define RSC_MAX 4

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
	compute->CBV("info", sizeof(param), index++);
	compute->CBV("param",  sizeof(param), index++);
	compute->UAV("input",  sizeof(float), sound->info.sample * sound->info.channel / sound->Offset(), index++);
	compute->UAV("output", sizeof(float), sound->info.sample * sound->info.channel / sound->Offset(), index++);
}

// ���s
void Effector::Execution(std::vector<float>& input)
{
	//�C��
	sound->comp.ratio = max(sound->comp.ratio, 0.01f);
	sound->comp.ratio = min(sound->comp.ratio, 1.0f);
	sound->distortion = max(sound->distortion, 1.0f);
	sound->toremor.depth = max(sound->toremor.depth, 0.0f);
	sound->toremor.depth = min(sound->toremor.depth, 1.0f);
	sound->toremor.rate = max(sound->toremor.rate, 0.0f);
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
	sound->volume = max(sound->volume, 0.0f);

	param = { sound->comp, sound->distortion, sound->toremor, float(sound->GetRead()), sound->pan, sound->volume };

	//�R�s�[
	compute->Copy("info",   sound->info);
	compute->Copy("param",  param);
	compute->Copy("input",  input);
	compute->Copy("output", input);

	//���s
	compute->Execution(uint(input.size()));

	//���f
	compute->UpData("output", input);
}
