#include "RootMane.h"
#include "Root.h"
#include "../etc/Release.h"
#include "../etc/Func.h"

// �R���X�g���N�^
RootMane::RootMane()
{
}

// �f�X�g���N�^
RootMane::~RootMane()
{
}

// ���[�g����
void RootMane::Create(const std::string& name, const std::string& fileName)
{
	if (root.find(name) != root.end())
	{
		return;
	}

	auto pass = func::ChangeCode(fileName);
	root[name] = std::make_shared<Root>(pass);
}

// ���[�g�폜
void RootMane::Delete(const std::string & name)
{
	if (root.find(name) != root.end())
	{
		root.erase(root.find(name));
	}
}

// �C���X�^���X�ϐ��擾
RootMane & RootMane::Get(void)
{
	static RootMane instance;
	return instance;
}

// ���[�g�擾
std::shared_ptr<Root> RootMane::GetRoot(const std::string & name)
{
	if (root.find(name) == root.end())
	{
		return nullptr;
	}

	return root[name];
}
