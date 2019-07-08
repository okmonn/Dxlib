#pragma once
#include <wrl.h>
#include <vector>
#include <memory>

struct ID3D12DescriptorHeap;
struct ID3D12Resource;
class List;
class Swap;

class Render
{
public:
	// コンストラクタ
	Render(std::weak_ptr<Swap>swap);
	// デストラクタ
	~Render();

	// 画面クリア
	void Clear(std::weak_ptr<List>list, ID3D12DescriptorHeap* depth = nullptr);

	// リソース取得
	ID3D12Resource* Get(void) const;

private:
	// ヒープ生成
	void CreateHeap(void);

	// リソース生成
	void CreateRsc(void);


	// スワップ
	std::weak_ptr<Swap>swap;

	// ヒープ
	Microsoft::WRL::ComPtr<ID3D12DescriptorHeap>heap;

	// リソース
	std::vector<Microsoft::WRL::ComPtr<ID3D12Resource>>rsc;
};
