#include "Effector.h"
#include "../Compute/Compute.h"
#include "Sound.h"

// リソース数
#define RSC_MAX 3

// コンストラクタ
Effector::Effector(Sound* sound) : 
	sound(sound)
{
	compute = std::make_unique<Compute>("MyLib/Shader/Effector.hlsl", RSC_MAX);
	param = {};

	Init();
}

// デストラクタ
Effector::~Effector()
{
}

// 初期化
void Effector::Init(void)
{
	uint index = 0;
	compute->CBV("param",  sizeof(param), index++);
	compute->UAV("input",  sizeof(float), sound->info.sample * sound->info.channel / sound->Offset(), index++);
	compute->UAV("output", sizeof(float), sound->info.sample * sound->info.channel / sound->Offset(), index++);
}

// 実行
void Effector::Execution(std::vector<float>& input)
{
	param = { sound->distortion, sound->compressor, sound->pan, sound->volume };

	//コピー
	compute->Copy("param",  param);
	compute->Copy("input",  input);
	compute->Copy("output", input);

	//実行
	compute->Execution(input.size());

	//反映
	compute->UpData("output", input);
}
