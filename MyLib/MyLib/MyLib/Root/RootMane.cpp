#include "RootMane.h"
#include "Root.h"
#include "../etc/Release.h"
#include "../etc/Func.h"

// コンストラクタ
RootMane::RootMane()
{
}

// デストラクタ
RootMane::~RootMane()
{
}

// ルート生成
void RootMane::Create(const std::string& name, const std::string& fileName)
{
	if (root.find(name) != root.end())
	{
		return;
	}

	auto pass = func::ChangeCode(fileName);
	root[name] = std::make_shared<Root>(pass);
}

// ルート削除
void RootMane::Delete(const std::string & name)
{
	if (root.find(name) != root.end())
	{
		root.erase(root.find(name));
	}
}

// インスタンス変数取得
RootMane & RootMane::Get(void)
{
	static RootMane instance;
	return instance;
}

// ルート取得
std::shared_ptr<Root> RootMane::GetRoot(const std::string & name)
{
	if (root.find(name) == root.end())
	{
		return nullptr;
	}

	return root[name];
}
