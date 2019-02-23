#pragma once
#include <string>
#include <memory>
#include <unordered_map>

class Root;

class RootMane
{
public:
	// デストラクタ
	~RootMane();

	// ルート生成
	void Create(const std::string& name, const std::string& fileName);

	// ルート削除
	void Delete(const std::string& name);

	// インスタンス変数取得
	static RootMane& Get(void);
	// ルート取得
	std::shared_ptr<Root> GetRoot(const std::string& name);

private:
	// コンストラクタ
	RootMane();
	RootMane(const RootMane&) = delete;
	void operator=(const RootMane&) = delete;


	// ルート
	std::unordered_map<std::string, std::shared_ptr<Root>>root;
};
