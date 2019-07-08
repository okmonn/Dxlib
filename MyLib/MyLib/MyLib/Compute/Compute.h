#pragma once
#include <wrl.h>
#include <string>
#include <vector>
#include <memory>

struct ID3D12DescriptorHeap;
struct ID3D12Resource;
class Queue;
class Allocator;
class List;
class Fence;
class Root;
class Pipe;

class Compute
{
	// ���\�[�X
	struct Resource {
		//���\�[�X
		Microsoft::WRL::ComPtr<ID3D12Resource>rsc;
		//���M�f�[�^
		void* data;

		Resource() : rsc(nullptr), data(nullptr) {}
	};

public:
	// �R���X�g���N�^
	Compute();
	// �f�X�g���N�^
	virtual ~Compute();

protected:
	// .hlsl�ǂݍ���
	void Compile(const std::string& fileName, const std::string& func, const std::string& ver = "cs_5_1");

	// .cso�ǂݍ���
	void Load(const std::string& fileName);

	// ���\�[�X�ǂݍ���
	void Read(const int& id);

	// �q�[�v����
	void CreateHeap(const size_t& num);

	// �萔���\�[�X����
	int CreateCRsc(const size_t& size);

	// �񏇏����\�[�X����
	int CreateURsc(const size_t& stride, const size_t& num);

	// GPU�������ɃR�s�[
	void Copy(const int& id, void* data, const size_t& size);

	// ���s
	void Execution(const unsigned int& x, const unsigned int& y = 1, const unsigned int& z = 1);

	// GPU�������f�[�^�擾
	template <typename T>
	std::vector<T> GetData(const int& id);

	// �I��
	void Finish(void);

private:
	// �L���[
	std::shared_ptr<Queue>queue;

	// �A���P�[�^
	std::shared_ptr<Allocator>allo;

	// ���X�g
	std::shared_ptr<List>list;

	// �t�F���X
	std::shared_ptr<Fence>fence;

	// ���[�g
	std::shared_ptr<Root>root;

	// �p�C�v
	std::shared_ptr<Pipe>pipe;

	// �q�[�v
	Microsoft::WRL::ComPtr<ID3D12DescriptorHeap>heap;

	// ���\�[�X
	std::vector<Resource>rsc;

	// �C���f�b�N�X
	unsigned char index;
};
