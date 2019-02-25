#pragma once
#include "../Vector/Vector3.h"
#include "../etc/Define.h"

class MyLib;

class WVP
{
	friend MyLib;

	// �萔
	struct Constant {
		//���[���h
		DirectX::XMFLOAT4X4 world;
		//�r���[
		DirectX::XMFLOAT4X4 view;
		//�v���W�F�N�V����
		DirectX::XMFLOAT4X4 projection;
	};

public:
	// �R���X�g���N�^
	WVP();
	// �f�X�g���N�^
	~WVP();

	// �J�����Z�b�g
	void SetCamera(const Vec3f& pos, const Vec3f& target, const Vec3f& upper, const Vec2f& winSize, const float& fov);

private:
	// ������
	void Init(void);

	// �J�����s��Z�b�g
	void SetCamera(void);


	// �q�[�v
	ID3D12DescriptorHeap* heap;

	// ���\�[�X
	ID3D12Resource* rsc;
	
	// �萔�f�[�^
	Constant* constant;

	// ���W
	Vec3f pos;

	// �^�[�Q�b�g
	Vec3f target;

	// ����
	Vec3f upper;

	// �E�B���h�E�T�C�Y
	Vec2f winSize;

	// ��p
	float fov;
};
