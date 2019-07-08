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
	// リソース
	struct Resource {
		//リソース
		Microsoft::WRL::ComPtr<ID3D12Resource>rsc;
		//送信データ
		void* data;

		Resource() : rsc(nullptr), data(nullptr) {}
	};

public:
	// コンストラクタ
	Compute();
	// デストラクタ
	virtual ~Compute();

protected:
	// .hlsl読み込み
	void Compile(const std::string& fileName, const std::string& func, const std::string& ver = "cs_5_1");

	// .cso読み込み
	void Load(const std::string& fileName);

	// リソース読み込み
	void Read(const int& id);

	// ヒープ生成
	void CreateHeap(const size_t& num);

	// 定数リソース生成
	int CreateCRsc(const size_t& size);

	// 非順序リソース生成
	int CreateURsc(const size_t& stride, const size_t& num);

	// GPUメモリにコピー
	void Copy(const int& id, void* data, const size_t& size);

	// 実行
	void Execution(const unsigned int& x, const unsigned int& y = 1, const unsigned int& z = 1);

	// GPUメモリデータ取得
	template <typename T>
	std::vector<T> GetData(const int& id);

	// 終了
	void Finish(void);

private:
	// キュー
	std::shared_ptr<Queue>queue;

	// アロケータ
	std::shared_ptr<Allocator>allo;

	// リスト
	std::shared_ptr<List>list;

	// フェンス
	std::shared_ptr<Fence>fence;

	// ルート
	std::shared_ptr<Root>root;

	// パイプ
	std::shared_ptr<Pipe>pipe;

	// ヒープ
	Microsoft::WRL::ComPtr<ID3D12DescriptorHeap>heap;

	// リソース
	std::vector<Resource>rsc;

	// インデックス
	unsigned char index;
};
