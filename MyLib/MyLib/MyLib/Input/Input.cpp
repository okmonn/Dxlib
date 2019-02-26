#include "Input.h"
#include <Windows.h>

// �R���X�g���N�^
Input::Input() : 
	key(std::nullopt)
{
}

// �f�X�g���N�^
Input::~Input()
{
}

// �L�[����
bool Input::CheckKey(const KeyCode & key)
{
	if (GetKeyState(int(key)) & 0x80)
	{
		this->key = key;
		return true;
	}

	return false;
}

// �g���K�[����
bool Input::Trigger(const KeyCode & key)
{
	if (this->key != key)
	{
		return CheckKey(key);
	}
	
	return false;
}

// �C���X�^���X�ϐ��擾
Input & Input::Get(void)
{
	static Input instance;
	return instance;
}
