#include "Mixer.h"
#include "../Waves/Waves.h"
#include "../DFT/DFT.h"
#include <MyLib.h>

#pragma comment(lib, "MyLib.lib")

//スレッド数
#define THREAD_MAX 2
// ウィンドウサイズ
const Vec2 winSize = { 640, 480 };

// コンストラクタ
Mixer::Mixer() : 
	play(false), threadFlag(true)
{
	auto size = func::GetDisplayResolution() / 2;
	lib = std::make_shared<MyLib>(winSize, size - winSize / 2);
	lib->ChangeTitle("MixeR");
	th.resize(THREAD_MAX);
}

// デストラクタ
Mixer::~Mixer()
{
	threadFlag = false;
	for (auto& i : th)
	{
		if (i.joinable() == true)
		{
			i.join();
		}
	}
}

// 処理
void Mixer::Run(void)
{
	while (lib->CheckMsg() && KEY.CheckKey(KeyCode::Escape) == false)
	{
		auto drop = lib->GetDropFilePass();
		if (drop.find(".wav") != std::string::npos)
		{
			if (sound != nullptr)
			{
				sound->Stop();
			}
			threadFlag = false;
			for (auto& i : th)
			{
				if (i.joinable() == true)
				{
					i.join();
				}
			}
			threadFlag = true;

			sound.reset(new Sound(drop));
			wave.reset(new Waves(lib, sound));
			th[0] = std::thread(&Mixer::DrawWaves, this);
			dft.reset(new DFT(lib, sound));
			th[1] = std::thread(&Mixer::DrawAmp, this);

			sound->Play(true);
			play = true;
		}

		if (KEY.Trigger(KeyCode::Space))
		{
			if (sound != nullptr)
			{
				if (play == true)
				{
					sound->Stop();
					play = false;
				}
				else
				{
					sound->Play(true);
					play = true;
				}
			}
		}
	}
}

// 波形描画
void Mixer::DrawWaves(void)
{
	while (threadFlag)
	{
		wave->Run();
	}
}

// 振幅
void Mixer::DrawAmp(void)
{
	while (threadFlag)
	{
		dft->Run();
	}
}
