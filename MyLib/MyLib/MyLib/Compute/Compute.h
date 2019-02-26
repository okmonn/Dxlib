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
	// コンストラクタ
	Compute();
	// デストラクタ
	virtual ~Compute();

	// 実行
	void Execution(const uint& x, const uint& y = 1, const uint& z = 1);

protected:
	// 初期化
	void Init(const std::string& fileName, const uint& num);

	// 定数リソース生成
	long CBV(const std::string& name, const size_t& size, const uint& index = 0);

	// UAVリソース生成
	long UAV(const std::string& name, const size_t& stride, const size_t& num, const uint& index = 0);

	// コピー
	template <typename T>
	void Copy(const std::string& name, const T& input);

	// 終了
	void End(void);


	// キュー
	std::shared_ptr<Queue>queue;

	// リスト
	std::unique_ptr<List>list;

	// フェンス
	std::unique_ptr<Fence>fence;

	// ルート
	std::shared_ptr<Root>root;

	// パイプ
	std::unique_ptr<Pipe>pipe;

	// ヒープ
	ID3D12DescriptorHeap* heap;

	// リソース
	std::unordered_map<std::string, ID3D12Resource*>rsc;

	// 送信データ
	std::unordered_map<std::string, void*>data;
};
