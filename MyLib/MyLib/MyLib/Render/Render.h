#pragma once
#include "../etc/Define.h"
#include <vector>
#include <memory>

class List;
class Swap;

class Render
{
public:
	// �R���X�g���N�^
	Render(std::weak_ptr<Swap>swap);
	// �f�X�g���N�^
	~Render();

	// �N���A
	void Clear(std::weak_ptr<List>list, ID3D12DescriptorHeap* depth = nullptr);

	// ���\�[�X�擾
	ID3D12Resource* Get(void) const;

private:
	// ������
	void Init(void);


	// �X���b�v
	std::weak_ptr<Swap>swap;

	// �q�[�v
	ID3D12DescriptorHeap* heap;

	// ���\�[�X
	std::vector<ID3D12Resource*>rsc;
};
