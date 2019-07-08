#pragma once
#include <wrl.h>
#include <memory>

class Window;
class Queue;
struct IDXGISwapChain4;

class Swap
{
public:
	// �R���X�g���N�^
	Swap(std::weak_ptr<Window>win, std::weak_ptr<Queue>queue);
	// �f�X�g���N�^
	~Swap();

	// �X���b�v�`�F�C���擾
	IDXGISwapChain4* Get(void) const;

private:
	// �X���b�v�`�F�C���̐���
	void CreateSwap(void);


	// �E�B���h�E
	std::weak_ptr<Window>win;

	// �L���[
	std::weak_ptr<Queue>queue;

	// �X���b�v�`�F�C��
	Microsoft::WRL::ComPtr<IDXGISwapChain4>swap;
};
