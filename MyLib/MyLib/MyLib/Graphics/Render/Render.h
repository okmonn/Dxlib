#pragma once
#include <wrl.h>
#include <vector>
#include <memory>

struct ID3D12DescriptorHeap;
struct ID3D12Resource;
class List;
class Swap;

class Render
{
public:
	// �R���X�g���N�^
	Render(std::weak_ptr<Swap>swap);
	// �f�X�g���N�^
	~Render();

	// ��ʃN���A
	void Clear(std::weak_ptr<List>list, ID3D12DescriptorHeap* depth = nullptr);

	// ���\�[�X�擾
	ID3D12Resource* Get(void) const;

private:
	// �q�[�v����
	void CreateHeap(void);

	// ���\�[�X����
	void CreateRsc(void);


	// �X���b�v
	std::weak_ptr<Swap>swap;

	// �q�[�v
	Microsoft::WRL::ComPtr<ID3D12DescriptorHeap>heap;

	// ���\�[�X
	std::vector<Microsoft::WRL::ComPtr<ID3D12Resource>>rsc;
};
