#pragma once
#include "Primitive/Primitive.h"
#include "Texture/Texture.h"
#include "etc/Func.h"
#include <unordered_map>

class Window;
class Queue;
class List;
class Fence;
class Swap;
class Render;
class Depth;
class Root;
class Pipe;

class MyLib
{
	// �萔
	struct Constant {
		//�J���[
		Vec3f color;
		//�A���t�@�l
		float alpha;
		//�E�B���h�E�T�C�Y
		Vec2f winSize;
	};

public:
	// �R���X�g���N�^
	MyLib(const Vec2& size, const Vec2& pos = 0x80000000);
	// �f�X�g���N�^
	~MyLib();

	// ���b�Z�[�W�̊m�F
	bool CheckMsg(void) const;

	// �N���A
	void Clear(void) const;

	// �v���~�e�B�u�`��
	void Draw(Primitive& primitive, const Vec3f& color, const float& alpha = 1.0f);

	// �摜�`��
	void Draw(Texture& tex, const float& alpha = 1.0f);

	// ���s
	void Execution(void) const;

private:
	//����֎~
	void operator=(const MyLib&) = delete;

	// ������
	void Init(void);

	// ���[�g�̃C���X�^���X
	void RootSignature(const std::string& name, const std::string& fileName);

	// �p�C�v�̃C���X�^���X
	void PipeLine(const std::string& name, const std::string& root, 
		const D3D12_PRIMITIVE_TOPOLOGY_TYPE& type, const std::initializer_list<uint>& index, const bool& depth);

	// �N���X�̃C���X�^���X��
	void Instance(const Vec2& pos);


	// �q�[�v
	ID3D12DescriptorHeap* heap;

	// ���\�[�X
	ID3D12Resource* rsc;

	// �萔�f�[�^
	Constant* constant;

	// �E�B���h�E
	std::shared_ptr<Window>win;

	// �L���[
	std::shared_ptr<Queue>queue;

	// ���X�g
	std::shared_ptr<List>list;

	// �t�F���X
	std::unique_ptr<Fence>fence;

	// �X���b�v
	std::shared_ptr<Swap>swap;

	// �����_�[
	std::unique_ptr<Render>render;

	// �f�v�X
	std::unique_ptr<Depth>depth;

	// ���[�g
	static std::unordered_map<std::string, std::shared_ptr<Root>>root;

	// �p�C�v
	static std::unordered_map<std::string, std::shared_ptr<Pipe>>pipe;
};
