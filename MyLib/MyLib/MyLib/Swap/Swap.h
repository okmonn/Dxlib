#pragma once
#include "../Vector/Vector2.h"
#include "../etc/Define.h"
#include <memory>

class Window;
class Queue;

class Swap
{
public:
	// �R���X�g���N�^
	Swap(std::weak_ptr<Window>win, std::weak_ptr<Queue>queue, const Vec2& size);
	// �f�X�g���N�^
	~Swap();

	// ���E�\��ʂ̑J��
	void Present(void) const;

	// �X���b�v�`�F�C���擾
	IDXGISwapChain4* Get(void) const;

private:
	// �X���b�v�`�F�C������
	long CreateSwap(std::weak_ptr<Window>win, std::weak_ptr<Queue>queue, const Vec2& size);


	// �X���b�v�`�F�C��
	IDXGISwapChain4* swap;
};
