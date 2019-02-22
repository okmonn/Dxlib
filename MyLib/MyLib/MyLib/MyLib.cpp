#include "MyLib.h"
#include "Window/Window.h"
#include "etc/Release.h"
#include <Windows.h>

#pragma comment(lib, "d3d12.lib")
#pragma comment(lib, "dxgi.lib")

// �R���X�g���N�^
MyLib::MyLib(const Vec2& size, const Vec2& pos)
{
	Instance(size, pos);
}

// �f�X�g���N�^
MyLib::~MyLib()
{
}

// �N���X�̃C���X�^���X��
void MyLib::Instance(const Vec2& size, const Vec2& pos)
{
	win = std::make_shared<Window>(pos, size);
}

// ���b�Z�[�W�̊m�F
bool MyLib::CheckMsg(void)
{
	static MSG msg{};

	if (msg.message == WM_QUIT)
	{
		return false;
	}

	//�Ăяo�����X���b�h�����L���Ă���E�B���h�E�ɑ��M���ꂽ���b�Z�[�W�ۗ̕�����Ă��镨���擾
	if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
	{
		//���z�L�[���b�Z�[�W�𕶎����b�Z�[�W�ɕϊ�
		TranslateMessage(&msg);
		//1�̃E�B�h�E�v���V�[�W���Ƀ��b�Z�[�W�𑗏o����
		DispatchMessage(&msg);
	}

	return true;
}
