#pragma once
#include "../etc/Define.h"
#include <string>
#include <vector>
#include <memory>

class List;
class MyLib;

// ���_���
struct Vertex {
	//���W
	Vec3f pos;
	//UV
	Vec2f uv;
};

// �e�N�X�`��
class Texture
{
	friend MyLib;

	// �萔
	struct Constant {
		//�s��
		DirectX::XMFLOAT4X4 matrix;
		//UV���W
		Vec2f uvPos;
		//UV�T�C�Y
		Vec2f uvSize;
		//���]
		Vec2f reverse;
	};

public:
	// ���W
	Vec3f pos;

	// �T�C�Y
	Vec2f size;

	// UV���W
	Vec2f uvPos;

	// UV�T�C�Y
	Vec2f uvSize;

	// ��]
	float rotate;

	// ���]�t���O
	Vec2 reverse;

	// �R���X�g���N�^
	Texture();
	Texture(const std::string& fileName);
	// �R�s�[�R���X�g���N�^
	Texture(const Texture& tex);
	// �f�X�g���N�^
	~Texture();

	// �ǂݍ���
	int Load(const std::string& fileName);

	// �e�N�X�`���T�C�Y�擾
	Vec2f GetTexSize(void) const;

	// ���Z�q�I�[�o�[���[�h
	void operator=(const Texture& tex);

private:
	// �萔���\�[�X����
	long CreateConstant(void);

	// ���_���\�[�X����
	long CreateVertex(void);

	// �T�u���\�[�X��������
	long WriteSub(const uint& index);

	// ������
	void Init(void);

	// �`�揀��
	uint SetDraw(std::weak_ptr<List>list);

	// ���_���擾
	uint GetVertexNum(void) const;

	// �q�[�v
	ID3D12DescriptorHeap* heap;

	// ���\�[�X
	std::vector<ID3D12Resource*>rsc;

	// �s��
	Constant* constant;

	// ���_���M�f�[�^
	void* data;

	// �t�@�C����
	std::string fileName;

	// ���_���
	static std::vector<Vertex>vertex;
};
