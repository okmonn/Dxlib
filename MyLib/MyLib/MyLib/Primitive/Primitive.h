#pragma once
#include "../Vector/Vector3.h"
#include "../etc/Define.h"
#include <vector>

// �^�C�v
enum class PrimitiveType {
	//�|�C���g
	point,
	//���C��
	line,
	//�g���C�A���O��
	triangle,
	//�{�b�N�X
	box
};

class Primitive
{
public:
	// �R���X�g���N�^
	Primitive();
	// �f�X�g���N�^
	~Primitive();

	// ������
	void Init(const PrimitiveType& type, const uint& num);


	// ���_�f�[�^
	std::vector<Vec3f>pos;

private:
	// ���\�[�X
	ID3D12Resource* rsc;

	// �^�C�v
	int type;
};
