#pragma once
#include <wrl.h>
#include <array>
#include <memory>

enum D3D12_RESOURCE_STATES : int;
enum D3D12_RESOURCE_FLAGS : int;
struct D3D12_HEAP_PROPERTIES;
struct ID3D12Resource;
class List;

class Acceleration
{
public:
	// �R���X�g���N�^
	Acceleration(std::weak_ptr<List>list, Acceleration* bottom = nullptr);
	// �f�X�g���N�^
	~Acceleration();

	// ���\�[�X�擾
	ID3D12Resource* Get(void) const;

private:
	// ���\�[�X����
	void CreateRsc(const unsigned int& id, const size_t& size, const D3D12_HEAP_PROPERTIES& prop, const D3D12_RESOURCE_STATES& state, const D3D12_RESOURCE_FLAGS& flag);

	// �g�b�v���x���\������
	void CreateTop(Acceleration* bottom);

	// �{�g�����x���\������
	void CreateBottom(ID3D12Resource* vertex, const size_t& stride);

	
	// ���X�g
	std::weak_ptr<List>list;

	// ���U���g�T�C�Y
	unsigned __int64 tlasSize;

	// ���\�[�X
	std::array<Microsoft::WRL::ComPtr<ID3D12Resource>, 3>rsc;
};
