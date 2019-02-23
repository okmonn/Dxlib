#pragma once
#include "../etc/Define.h"
#include <vector>
#include <memory>

class List;
class Swap;

class Render
{
public:
	// コンストラクタ
	Render(std::weak_ptr<Swap>swap);
	// デストラクタ
	~Render();

	// クリア
	void Clear(std::weak_ptr<List>list, ID3D12DescriptorHeap* depth = nullptr);

	// リソース取得
	ID3D12Resource* Get(void) const;

private:
	// 初期化
	void Init(void);


	// スワップ
	std::weak_ptr<Swap>swap;

	// ヒープ
	ID3D12DescriptorHeap* heap;

	// リソース
	std::vector<ID3D12Resource*>rsc;
};
