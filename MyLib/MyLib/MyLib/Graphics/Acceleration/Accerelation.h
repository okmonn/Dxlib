#pragma once
#include <wrl.h>
#include <array>
#include <memory>

struct ID3D12Resource;
class List;

class Acceleration
{
public:
	// �R���X�g���N�^
	Acceleration(std::weak_ptr<List>list);
	// �f�X�g���N�^
	~Acceleration();

private:
	// �g�b�v���x���\������
	void CreateTop(void);

	// �{�g�����x���\������
	void CreateBottom(ID3D12Resource* vertex, const size_t& stride);

	
	// ���X�g
	std::weak_ptr<List>list;

	// ���\�[�X
	std::array<Microsoft::WRL::ComPtr<ID3D12Resource>, 3>rsc;
};
