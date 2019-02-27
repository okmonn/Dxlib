#pragma once
#include "../etc/Define.h"
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>

class Queue;
class List;
class Fence;
class Root;
class Pipe;

// �R���s���[�g
class Compute
{
public:
	// �R���X�g���N�^
	Compute(const std::string& fileName, const uint& num);
	// �f�X�g���N�^
	~Compute();

	// �萔���\�[�X����
	long CBV(const std::string& name, const size_t& size, const uint& index = 0);

	// UAV���\�[�X����
	long UAV(const std::string& name, const size_t& stride, const size_t& num, const uint& index = 0);

	// �R�s�[
	template <typename T>
	void Copy(const std::string& name, const T& input);
	template <typename T>
	void Copy(const std::string& name, const std::vector<T>& input);

	// ���s
	void Execution(const uint& x = 1, const uint& y = 1, const uint& z = 1);

	// ���f
	template <typename T>
	void UpData(const std::string& name, std::vector<T>& output);

protected:
	Compute(const Compute&) = delete;
	void operator=(const Compute&) = delete;


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

// �R�s�[
template<typename T>
void Compute::Copy(const std::string& name, const T& input)
{
	if (rsc.find(name) == rsc.end())
	{
		return;
	}

	memcpy(data[name], &input, sizeof(input));
}

// �R�s�[
template<typename T>
void Compute::Copy(const std::string & name, const std::vector<T>& input)
{
	if (rsc.find(name) == rsc.end())
	{
		return;
	}

	memcpy(data[name], input.data(), sizeof(input[0]) * input.size());
}
