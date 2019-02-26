#pragma once
#include "../etc/Define.h"
#include <memory>

class Root;

// �p�C�v���C��
class Pipe
{
public:
	// �R���X�g���N�^
	Pipe(std::weak_ptr<Root>root, const D3D12_INPUT_ELEMENT_DESC& input, const size_t& num, const D3D12_PRIMITIVE_TOPOLOGY_TYPE& type, const bool& depth);
	Pipe(std::weak_ptr<Root>root);
	// �f�X�g���N�^
	~Pipe();

	// �p�C�v���C���擾
	ID3D12PipelineState* Get(void) const;

private:
	Pipe(const Pipe&) = delete;
	void operator=(const Pipe&) = delete;

	// �`��p�p�C�v���C������
	long Graphic(const D3D12_INPUT_ELEMENT_DESC& input, const size_t& num, const D3D12_PRIMITIVE_TOPOLOGY_TYPE& type, const bool& depth);

	// �v�Z�p�p�C�v���C������
	long Compute(void);


	// ���[�g
	std::weak_ptr<Root>root;

	// �p�C�v���C��
	ID3D12PipelineState* pipe;
};
