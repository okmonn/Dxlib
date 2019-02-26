#pragma once
#include "../etc/Define.h"
#include <memory>

class Queue;

// �t�F���X
class Fence
{
public:
	// �R���X�g���N�^
	Fence(std::weak_ptr<Queue>queue);
	// �f�X�g���N�^
	~Fence();

	// �ҋ@
	void Wait(void);

private:
	Fence(const Fence&) = delete;
	void operator=(const Fence&) = delete;

	// �t�F���X����
	long CreateFence(void);


	// �L���[
	std::weak_ptr<Queue>queue;

	// �t�F���X
	ID3D12Fence* fence;

	// �C�x���g�n���h��
	void* handle;

	// �t�F���X�J�E���g
	uint64 cnt;
};
