#pragma once
#include "Input/Input.h"
#include "Primitive/Primitive.h"
#include "Texture/Texture.h"
#include "Sound/Sound.h"
#include "Compute/Compute.h"
#include "etc/Func.h"

#define KEY Input::Get()

class Window;
class Queue;
class List;
class Fence;
class Swap;
class Render;
class Depth;
class Root;
class Pipe;

// �������񎩍색�C�u����
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
	MyLib(const MyLib& mylib, const Vec2& size, const Vec2& pos = 0x80000000);
	MyLib(std::weak_ptr<MyLib> mylib, const Vec2& size, const Vec2& pos = 0x80000000);
	// �f�X�g���N�^
	~MyLib();

	// �^�C�g�����ύX
	void ChangeTitle(const std::string& title);

	// �h���b�v���ꂽ�t�@�C���p�X�擾
	std::string GetDropFilePass(void);

	// �E�B���h�E���W�擾
	Vec2 GetWinPos(void);

	// �E�B���h�E�T�C�Y�擾
	Vec2 GetWinSize(void);

	// �}�E�X���W�擾
	Vec2 GetMousePos(void);

	// �}�E�X�z�C�[���ʎ擾
	int GetMouseWheel(void) const;

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
	MyLib(const MyLib&) = delete;
	void operator=(const MyLib&) = delete;

	// ������
	void Init(void);

	// ���[�g�̃C���X�^���X
	template <typename T>
	void RootSignature(const std::string& name, const std::initializer_list<T>& id);

	// �p�C�v�̃C���X�^���X
	void PipeLine(const std::string& name, const std::string& root, 
		const D3D12_PRIMITIVE_TOPOLOGY_TYPE& type, const std::initializer_list<uint>& index, const bool& depth);

	// �N���X�̃C���X�^���X��
	void Instance(const Vec2& pos, void* parent = nullptr);


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
