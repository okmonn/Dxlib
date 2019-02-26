#pragma once
#include "../etc/Define.h"
#include <memory>

class Window;
class Queue;

// �X���b�v�`�F�C��
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
	Swap(const Swap&) = delete;
	void operator=(const Swap&) = delete;

	// �X���b�v�`�F�C������
	long CreateSwap(std::weak_ptr<Window>win, std::weak_ptr<Queue>queue, const Vec2& size);


	// �X���b�v�`�F�C��
	IDXGISwapChain4* swap;
};
