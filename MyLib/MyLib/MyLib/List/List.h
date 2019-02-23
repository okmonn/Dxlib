#pragma once
#include "../Vector/Vector2.h"
#include "../etc/Define.h"

class List
{
public:
	// �R���X�g���N�^
	List(const D3D12_COMMAND_LIST_TYPE& type);
	// �f�X�g���N�^
	~List();

	// ���Z�b�g
	void Reset(ID3D12PipelineState* pipe = nullptr) const;

	// �r���[�|�[�g�Z�b�g
	void Viewport(const Vec2& size) const;

	// �V�U�[�Z�b�g
	void Scissor(const Vec2& size) const;

	// �o���A�Z�b�g
	void Barrier(const D3D12_RESOURCE_STATES& befor, const D3D12_RESOURCE_STATES& affter, ID3D12Resource* rsc) const;

	// �`��p���[�g�Z�b�g
	void GraphicRoot(ID3D12RootSignature* root) const;

	// �v�Z�p���[�g�Z�b�g
	void ComputeRoot(ID3D12RootSignature* root) const;

	// �p�C�v���C���Z�b�g
	void Pipeline(ID3D12PipelineState* pipe) const;

	// �q�[�v�Z�b�g
	void Heap(ID3D12DescriptorHeap** heap, const size_t& num) const;

	// �`��p���[�g�ƃq�[�v�֘A�t��
	void GraphicTable(const uint& id, ID3D12DescriptorHeap* heap, const uint& index = 0) const;

	// �v�Z�p���[�g�ƃq�[�v�֘A�t��
	void ComputeTable(const uint& id, ID3D12DescriptorHeap* heap, const uint& index = 0) const;

	// ���_�o�b�t�@�r���[�Z�b�g
	void VertexView(const D3D12_VERTEX_BUFFER_VIEW& view) const;

	// �C���f�b�N�X�o�b�t�@�r���[�Z�b�g
	void IndexView(const D3D12_INDEX_BUFFER_VIEW& view) const;

	// �g�|���W�[�Z�b�g
	void Topology(const D3D_PRIMITIVE_TOPOLOGY& type) const;

	// ���_�`��
	void DrawVertex(const size_t& num, const uint& instance = 1) const;

	// �o���h�����s
	void Bundle(ID3D12GraphicsCommandList* list) const;

	// GPU�v�Z���s
	void Dispatch(const uint& x, const uint& y, const uint& z) const;

	// �N���[�Y
	void Close(void) const;

	// �A���P�[�^�擾
	ID3D12CommandAllocator* GetAllo(void) const;
	// ���X�g�擾
	ID3D12GraphicsCommandList* GetList(void) const;

private:
	// �A���P�[�^����
	long CreateAllo(const D3D12_COMMAND_LIST_TYPE& type);

	// ���X�g����
	long CreateList(const D3D12_COMMAND_LIST_TYPE& type);

	// ������
	void Init(const D3D12_COMMAND_LIST_TYPE& type);

	
	// �A���P�[�^
	ID3D12CommandAllocator* allo;

	// ���X�g
	ID3D12GraphicsCommandList* list;
};
