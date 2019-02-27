#pragma once
#include "KeyCode.h"
#include "../etc/Define.h"

// �C���v�b�g
class Input
{
public:
	// �f�X�g���N�^
	~Input();

	// �L�[����
	bool CheckKey(const KeyCode& key);

	// �g���K�[����
	bool Trigger(const KeyCode& key);

	// �C���X�^���X�ϐ��擾
	static Input& Get(void);

private:
	Input();
	Input(const Input&) = delete;
	void operator=(const Input&) = delete;


	// ���݂̓��̓L�[�R�[�h
	uint now[256];

	// �ߋ��̓��̓L�[�R�[�h
	uint old[256];
};
