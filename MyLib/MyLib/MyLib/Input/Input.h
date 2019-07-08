#pragma once
#include "../etc/Single.h"
#include <array>

namespace okmonn {
	enum class KeyCode;
}

class Input :
	public Single<Input>
{
	friend Single<Input>;
public:
	// �L�[����
	bool CheckKey(const okmonn::KeyCode& key);

	// �g���K�[����
	bool Trigger(const okmonn::KeyCode& key);

private:
	// �R���X�g���N�^
	Input();
	// �f�X�g���N�^
	~Input();

	
	// ���݂̏��
	std::array<unsigned char, 256>now;

	// �ߋ��̏��
	std::array<unsigned char, 256>old;
};
