#include "Input.h"
#include "KeyCode.h"
#include <Windows.h>

// �R���X�g���N�^
Input::Input()
{
	std::fill(now.begin(), now.end(), 0);
	std::fill(old.begin(), old.end(), 0);
}

// �f�X�g���N�^
Input::~Input()
{
}

// �L�[����
bool Input::CheckKey(const okmonn::KeyCode& key)
{
	old[unsigned char(key)] = now[unsigned char(key)];
	now[unsigned char(key)] = (GetKeyState(unsigned char(key)) & 0x80);
	if (now[unsigned char(key)])
	{
		return true;
	}

	return false;
}

// �g���K�[����
bool Input::Trigger(const okmonn::KeyCode& key)
{
	if (CheckKey(key) == true
		&& now[unsigned char(key)] != old[unsigned char(key)])
	{
		return true;
	}

	return false;
}
