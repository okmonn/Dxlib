#pragma once
#include "../etc/Define.h"

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
	// �L���[����
	long CreateQueue(const D3D12_COMMAND_LIST_TYPE& type);


	// �L���[
	ID3D12CommandQueue* queue;
};
