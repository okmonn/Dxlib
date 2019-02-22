#pragma once
#include "Vector/Vector2.h"
#include <memory>

class Window;
class Queue;
class List;

class MyLib
{
public:
	// �R���X�g���N�^
	MyLib(const Vec2& size, const Vec2& pos = 0x80000000);
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

	// �L���[
	std::shared_ptr<Queue>queue;

	// ���X�g
	std::shared_ptr<List>list;
};
