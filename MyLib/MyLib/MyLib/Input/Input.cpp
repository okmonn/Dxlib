#include "Input.h"
#include <windows.h>

// �R���X�g���N�^
Input::Input()
{
	memset(&now[0], 0, sizeof(now));
	memset(&old[0], 0, sizeof(old));
}

// �f�X�g���N�^
Input::~Input()
{
}

// �L�[����
bool Input::CheckKey(const KeyCode & key)
{
	old[uint(key)] = now[uint(key)];
	now[uint(key)] = (GetKeyState(uint(key)) & 0x80);
	if (now[uint(key)])
	{
		return true;
	}

	return false;
}

// �g���K�[����
bool Input::Trigger(const KeyCode & key)
{
	if (CheckKey(key) == true 
		&& now[uint(key)] != old[uint(key)])
	{
		return true;
	}

	return false;
}

// �C���X�^���X�ϐ��擾
Input & Input::Get(void)
{
	static Input instance;
	return instance;
}
