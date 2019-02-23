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
	// デストラクタ
	~PipeMane();

	// パイプ生成
	void Create(const std::string& name, std::weak_ptr<Root>root, const D3D12_PRIMITIVE_TOPOLOGY_TYPE& type, const std::initializer_list<std::string>& input, const bool& depth);
	void Create(const std::string& name, std::weak_ptr<Root>root);

	// パイプ削除
	void Delete(const std::string& name);

	// インスタンス変数取得
	static PipeMane& Get(void);
	// パイプ取得
	std::shared_ptr<Pipe> GetPipe(const std::string& name);

private:
	// コンストラクタ
	PipeMane();
	PipeMane(const PipeMane&) = delete;
	void operator=(const PipeMane&) = delete;


	// パイプ
	std::unordered_map<std::string, std::shared_ptr<Pipe>>pipe;
};
