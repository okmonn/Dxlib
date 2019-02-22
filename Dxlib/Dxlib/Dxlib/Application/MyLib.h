#pragma once
#include "../Vector/Vector2.h"
#include <memory>

class Window;

class MyLib
{
public:
	// �R���X�g���N�^
	inline MyLib(const Vec2& size, const Vec2& pos = 0x80000000);
	// �f�X�g���N�^
	~MyLib();

	// ���b�Z�[�W�̊m�F
	bool CheckMsg(void);

private:
	//����֎~
	void operator=(const MyLib&) = delete;

	// �N���X�̃C���X�^���X��
	void Instance(const Vec2& size, const Vec2& pos);


	// �E�B���h�E
	std::shared_ptr<Window>win;
};
