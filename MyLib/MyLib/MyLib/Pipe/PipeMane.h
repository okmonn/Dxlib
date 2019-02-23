#pragma once
#include "../etc/Define.h"
#include <string>
#include <memory>
#include <unordered_map>

class Root;
class Pipe;

class PipeMane
{
public:
	// �f�X�g���N�^
	~PipeMane();

	// �p�C�v����
	void Create(const std::string& name, std::weak_ptr<Root>root, const D3D12_PRIMITIVE_TOPOLOGY_TYPE& type, const std::initializer_list<std::string>& input, const bool& depth);
	void Create(const std::string& name, std::weak_ptr<Root>root);

	// �p�C�v�폜
	void Delete(const std::string& name);

	// �C���X�^���X�ϐ��擾
	static PipeMane& Get(void);
	// �p�C�v�擾
	std::shared_ptr<Pipe> GetPipe(const std::string& name);

private:
	// �R���X�g���N�^
	PipeMane();
	PipeMane(const PipeMane&) = delete;
	void operator=(const PipeMane&) = delete;


	// �p�C�v
	std::unordered_map<std::string, std::shared_ptr<Pipe>>pipe;
};
