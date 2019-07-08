#pragma once
#include <wrl.h>
#include <memory>

enum D3D12_PRIMITIVE_TOPOLOGY_TYPE;
struct ID3D12PipelineState;
struct D3D12_INPUT_ELEMENT_DESC;
class Root;

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
	// �p�C�v���C������
	void CreatePipe(std::weak_ptr<Root>root, const D3D12_INPUT_ELEMENT_DESC& input, const size_t& num, const D3D12_PRIMITIVE_TOPOLOGY_TYPE& type, const bool& depth);
	void Create(std::weak_ptr<Root>root);

	// �p�C�v���C��
	Microsoft::WRL::ComPtr<ID3D12PipelineState>pipe;
};
