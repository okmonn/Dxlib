#pragma once
#include "KeyCode.h"
#include <optional>

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


	// �O�̓��̓L�[�R�[�h
	std::optional<KeyCode>key;
};
