#pragma once
#include "../etc/Define.h"

// �R�}���h�L���[
class Queue
{
public:
	// �R���X�g���N�^
	Queue(const D3D12_COMMAND_LIST_TYPE& type);
	// �f�X�g���N�^
	~Queue();

	// ���s
	void Execution(ID3D12CommandList ** list, const size_t & num);

	// �L���[�擾
	ID3D12CommandQueue* Get(void) const;

private:
	Queue(const Queue&) = delete;
	void operator=(const Queue&) = delete;

	// �L���[����
	long CreateQueue(const D3D12_COMMAND_LIST_TYPE& type);


	// �L���[
	ID3D12CommandQueue* queue;
};
