#pragma once
#include "../etc/Define.h"
#include <memory>

class List;

// 深度ステンシル
class Depth
{
public:
	// コンストラクタ
	Depth(const Vec2& size);
	// デストラクタ
	~Depth();

	// クリア
	void Clear(std::weak_ptr<List>list);

	// ヒープ取得
	ID3D12DescriptorHeap* Get(void) const;

private:
	Depth(const Depth&) = delete;
	void operator=(const Depth&) = delete;

	// 初期化
	void Init(const Vec2& size);


	// ヒープ
	ID3D12DescriptorHeap* heap;

	// リソース
	ID3D12Resource* rsc;
};
