#include "Waves.h"
#include <MyLib.h>
#include <minmax.h>

// ウィンドウサイズ
const Vec2 winSize = { 400, 480 };

// コンストラクタ
Waves::Waves(std::weak_ptr<MyLib>lib, std::weak_ptr<Sound>sound) : 
	sound(sound), flam(0)
{	this->lib = std::make_unique<MyLib>(lib, winSize, Vec2(lib.lock()->GetWinPos().x - winSize.x, lib.lock()->GetWinPos().y));
	prim      = std::make_unique<Primitive>();
	
	this->lib->ChangeTitle("波形");
}

// デストラクタ
Waves::~Waves()
{
}

// 処理
void Waves::Run(void)
{
	if (sound.expired())
	{
		return;
	}

	prim->Init(PrimitiveType::line, (sound.lock()->info.sample / sound.lock()->Offset() * 2));
	
	const float width = float(winSize.x) / float(prim->pos.size() / 2);

	++flam;

	lib->Clear();
	lib->Draw(*prim, Vec3f(1.0f, 0.0f, 0.0f));
	lib->Execution();

	//5フレームごとに更新
	if (flam % 5 != 0)
	{
		return;
	}

	auto wave = sound.lock()->GetWave();
	uint index = 0;
	for (uint i = 0; i < prim->pos.size(); i += 2)
	{
		prim->pos[i] = Vec2f(width * i / 2, float(winSize.y / 2));
		prim->pos[i + 1] = prim->pos[i];
		float tmp = 0.0f;
		for (uint ch = 0; ch < sound.lock()->info.channel; ++ch)
		{
			tmp += wave[index * sound.lock()->info.channel + ch];
		}
		prim->pos[i + 1].y -= tmp * 100;
		++index;
	}
	flam = 0;
}
