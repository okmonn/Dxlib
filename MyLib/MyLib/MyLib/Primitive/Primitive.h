#pragma once
#include "../Vector/Vector3.h"
#include "../etc/Define.h"
#include <vector>

class MyLib;

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
	friend MyLib;
public:
	// ���_�f�[�^
	std::vector<Vec3f>pos;


	// �R���X�g���N�^
	Primitive();
	Primitive(const PrimitiveType& type);
	Primitive(const PrimitiveType& type, const uint& num);
	// �R�s�[�R���X�g���N�^
	Primitive(const Primitive& prim);
	// �f�X�g���N�^
	~Primitive();

	// ������
	void Init(const PrimitiveType& type, const uint& num);

	// ���Z�q�I�[�o�[���[�h
	void operator=(const Primitive& prim);

private:
	// �f�[�^�X�V
	void UpData(void) const;


	// ���\�[�X
	ID3D12Resource* rsc;

	// ���M�f�[�^
	void* data;

	// �^�C�v
	int type;
};
