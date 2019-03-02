#include "DFT.h"
#include <MyLib.h>

// リソース数
#define RSC_MAX 3
// ウィンドウサイズ
const Vec2 winSize = { 400, 480 };

// コンストラクタ
DFT::DFT(std::weak_ptr<MyLib>lib, std::weak_ptr<Sound>sound) : 
	sound(sound)
{
	this->lib = std::make_unique<MyLib>(lib, winSize, Vec2(lib.lock()->GetWinPos().x + lib.lock()->GetWinSize().x, lib.lock()->GetWinPos().y));
	compute   = std::make_unique<Compute>("DFT/DFT.hlsl", "CS", "cs_5_1", RSC_MAX);
	prim      = std::make_unique<Primitive>();

	this->lib->ChangeTitle("振幅スペクトル");
	Init();
}

// デストラクタ
DFT::~DFT()
{
}

// 初期化
void DFT::Init(void)
{
	const uint num = sound.lock()->info.sample / sound.lock()->Offset();

	uint index = 0;
	compute->UAV("input", sizeof(float), num, index++);
	compute->UAV("real", sizeof(float), num, index++);
	compute->UAV("imag", sizeof(float), num, index++);
}

// 処理
void DFT::Run(void)
{
	if (sound.expired())
	{
		return;
	}

	prim->Init(PrimitiveType::line, (sound.lock()->info.sample / sound.lock()->Offset() * 2));

	const float width = float(winSize.x) / float(prim->pos.size() / 2);

	auto wave = sound.lock()->GetWave();
	std::vector<float>tmp(wave.size() / sound.lock()->info.channel);
	for (uint i = 0; i < tmp.size(); ++i)
	{
		for (uint ch = 0; ch < sound.lock()->info.channel; ++ch)
		{
			tmp[i] += wave[i * sound.lock()->info.channel + ch];
		}
	}

	compute->Copy("input", tmp);
	compute->Execution(tmp.size());
	compute->UpData("real", real);
	compute->UpData("imag", imag);

	uint index = 0;
	for (uint i = 0; i < prim->pos.size(); i += 2)
	{
		prim->pos[i] = Vec2f(width * i / 2, float(winSize.y));
		prim->pos[i + 1] = prim->pos[i];
		auto a = func::Amplitude(real[index], imag[index]);
		prim->pos[i + 1].y -= a * 0.5f;
		++index;
	}

	lib->Clear();
	lib->Draw(*prim, Vec3f(1.0f, 0.0f, 0.0f));
	lib->Execution();
}
