#pragma once
#include "../etc/Define.h"
#include <memory>

class List;

// �[�x�X�e���V��
class Depth
{
public:
	// �R���X�g���N�^
	Depth(const Vec2& size);
	// �f�X�g���N�^
	~Depth();

	// �N���A
	void Clear(std::weak_ptr<List>list);

	// �q�[�v�擾
	ID3D12DescriptorHeap* Get(void) const;

private:
	Depth(const Depth&) = delete;
	void operator=(const Depth&) = delete;

	// ������
	void Init(const Vec2& size);


	// �q�[�v
	ID3D12DescriptorHeap* heap;

	// ���\�[�X
	ID3D12Resource* rsc;
};
