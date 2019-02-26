#include "Fence.h"
#include "../Queue/Queue.h"
#include "../etc/Func.h"
#include "../etc/Release.h"

// �R���X�g���N�^
Fence::Fence(std::weak_ptr<Queue>queue) : queue(queue),
	fence(nullptr), handle(CreateEventEx(nullptr, false, false, EVENT_ALL_ACCESS)), cnt(0)
{
	CreateFence();
}

// �f�X�g���N�^
Fence::~Fence()
{
	Release(fence);
	CloseHandle(handle);
}

// �t�F���X����
long Fence::CreateFence(void)
{
	auto hr = Dev->CreateFence(cnt, D3D12_FENCE_FLAGS::D3D12_FENCE_FLAG_NONE, IID_PPV_ARGS(&fence));
	if (FAILED(hr))
	{
		func::DebugLog("�t�F���X�����F���s");
		return hr;
	}

	cnt = 1;

	return hr;
}

// �ҋ@
void Fence::Wait(void)
{
	//�t�F���X�l�X�V
	++cnt;

	//�t�F���X�l��ύX
	auto hr = queue.lock()->Get()->Signal(fence, cnt);
	if (FAILED(hr))
	{
		func::DebugLog("�t�F���X�l�X�V�F���s");
		return;
	}

	//������ҋ@(�|�[�����O)
	while (fence->GetCompletedValue() != cnt)
	{
		//�t�F���X�C�x���g�̃Z�b�g
		hr = fence->SetEventOnCompletion(cnt, handle);
		if (FAILED(hr))
		{
			func::DebugLog("�t�F���X�C�x���g�Z�b�g�F���s");
			return;
		}

		//�t�F���X�C�x���g�̑ҋ@
		WaitForSingleObject(handle, INFINITE);
	}
}
