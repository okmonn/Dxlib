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

// コンピュート
class Compute
{
public:
	// コンストラクタ
	Compute(const std::string& fileName, const uint& num);
	// デストラクタ
	~Compute();

	// 定数リソース生成
	long CBV(const std::string& name, const size_t& size, const uint& index = 0);

	// UAVリソース生成
	long UAV(const std::string& name, const size_t& stride, const size_t& num, const uint& index = 0);

	// コピー
	template <typename T>
	void Copy(const std::string& name, const T& input);
	template <typename T>
	void Copy(const std::string& name, const std::vector<T>& input);

	// 実行
	void Execution(const uint& x = 1, const uint& y = 1, const uint& z = 1);

	// 反映
	template <typename T>
	void UpData(const std::string& name, std::vector<T>& output);

protected:
	Compute(const Compute&) = delete;
	void operator=(const Compute&) = delete;


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

// コピー
template<typename T>
void Compute::Copy(const std::string& name, const T& input)
{
	if (rsc.find(name) == rsc.end())
	{
		return;
	}

	memcpy(data[name], &input, sizeof(input));
}

// コピー
template<typename T>
void Compute::Copy(const std::string & name, const std::vector<T>& input)
{
	if (rsc.find(name) == rsc.end())
	{
		return;
	}

	memcpy(data[name], input.data(), sizeof(input[0]) * input.size());
}
