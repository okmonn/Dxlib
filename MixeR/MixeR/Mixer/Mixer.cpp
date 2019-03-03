#include "Mixer.h"
#include "../Mouse/Mouse.h"
#include "../ParamMane/ParamMane.h"
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
	mouse = std::make_shared<Mouse>(lib);
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

// リセット
void Mixer::Reset(void)
{
	auto drop = lib->GetDropFilePass();
	if (drop.find(".wav") == std::string::npos)
	{
		return;
	}

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
	param.reset(new ParamMane(lib, sound, mouse));
	wave.reset(new Waves(lib, sound));
	th[0] = std::thread(&Mixer::DrawWaves, this);
	dft.reset(new DFT(lib, sound));
	th[1] = std::thread(&Mixer::DrawAmp, this);

	sound->Play(true);
	play = true;
}

// 処理
void Mixer::UpData(void)
{
	mouse->UpData();

	if (param == nullptr)
	{
		return;
	}

	lib->Clear();
	param->Draw();
	param->UpData();
	lib->Execution();
}

// 再生・停止
void Mixer::PlayAndStop(void)
{
	if (sound == nullptr)
	{
		return;
	}

	if (KEY.Trigger(KeyCode::Space))
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

// 処理
void Mixer::Run(void)
{
	while (lib->CheckMsg() && KEY.CheckKey(KeyCode::Escape) == false)
	{
		Reset();

		UpData();

		PlayAndStop();
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
