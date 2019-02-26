#pragma once
#include "../etc/Define.h"
#include <string>
#include <memory>
#include <unordered_map>

class Queue;
class List;
class Fence;
class Root;
class Pipe;

class Compute
{
public:
	// �R���X�g���N�^
	Compute();
	// �f�X�g���N�^
	virtual ~Compute();

	// ���s
	void Execution(const uint& x, const uint& y = 1, const uint& z = 1);

protected:
	// ������
	void Init(const std::string& fileName, const uint& num);

	// �萔���\�[�X����
	long CBV(const std::string& name, const size_t& size, const uint& index = 0);

	// UAV���\�[�X����
	long UAV(const std::string& name, const size_t& stride, const size_t& num, const uint& index = 0);

	// �R�s�[
	template <typename T>
	void Copy(const std::string& name, const T& input);

	// �I��
	void End(void);


	// �L���[
	std::shared_ptr<Queue>queue;

	// ���X�g
	std::unique_ptr<List>list;

	// �t�F���X
	std::unique_ptr<Fence>fence;

	// ���[�g
	std::shared_ptr<Root>root;

	// �p�C�v
	std::unique_ptr<Pipe>pipe;

	// �q�[�v
	ID3D12DescriptorHeap* heap;

	// ���\�[�X
	std::unordered_map<std::string, ID3D12Resource*>rsc;

	// ���M�f�[�^
	std::unordered_map<std::string, void*>data;
};
