#include "Effector.h"
#include "../Compute/Compute.h"
#include "Sound.h"

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
	param = { sound->distortion, sound->compressor, sound->pan, sound->volume };

	//�R�s�[
	compute->Copy("param",  param);
	compute->Copy("input",  input);
	compute->Copy("output", input);

	//���s
	compute->Execution(input.size());

	//���f
	compute->UpData("output", input);
}
