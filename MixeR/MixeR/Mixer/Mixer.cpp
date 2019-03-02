#include "Mixer.h"
#include <MyLib.h>
#include <optional>

#pragma comment(lib, "MyLib.lib")

// �E�B���h�E�T�C�Y
Vec2 winSize = { 640, 480 };

// �R���X�g���N�^
Mixer::Mixer()
{
	lib = std::make_shared<MyLib>(winSize);
}

// �f�X�g���N�^
Mixer::~Mixer()
{
}

// ����
void Mixer::Run(void)
{
	Sound sound;
	while (lib->CheckMsg() && KEY.CheckKey(KeyCode::Escape) == false)
	{
		if (lib->GetDropFilePass() != std::nullopt)
		{
			sound.Load(lib->GetDropFilePass().value());
			sound.Play(false);
		}
	}
}
