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
	prim      = std::make_unique<Primitive>();

	this->lib->ChangeTitle("振幅スペクトル");
}

// デストラクタ
DFT::~DFT()
{
}

// 処理
void DFT::Run(void)
{
	if (sound.expired())
	{
		return;
	}

	auto wave = sound.lock()->GetWave();
	std::vector<float>tmp(wave.size() / sound.lock()->info.channel);
	for (uint i = 0; i < tmp.size(); ++i)
	{
		for (uint ch = 0; ch < sound.lock()->info.channel; ++ch)
		{
			tmp[i] += wave[i * sound.lock()->info.channel + ch];
		}
	}
	const float width = float(winSize.x) / float(tmp.size());

	func::DFT(tmp, real, imag);
	prim->Init(PrimitiveType::line, (sound.lock()->info.sample / sound.lock()->Offset() * 2));
	uint index = 0;
	for (uint i = 0; i < prim->pos.size(); i += 2)
	{
		prim->pos[i] = Vec2f(width * i / 2, float(winSize.y / 2));
		prim->pos[i + 1] = prim->pos[i];
		auto a = func::Amplitude(real[index], imag[index]);
		prim->pos[i + 1].y -= a;
		++index;
	}

	lib->Clear();
	lib->Draw(*prim, Vec3f(1.0f, 0.0f, 0.0f));
	lib->Execution();
}
