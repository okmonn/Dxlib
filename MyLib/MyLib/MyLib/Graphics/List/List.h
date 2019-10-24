#pragma once
#include "../../etc/Vector2.h"
#include <wrl.h>
#include <memory>

enum D3D12_COMMAND_LIST_TYPE : int;
enum D3D12_RESOURCE_STATES : int;
struct ID3D12GraphicsCommandList5;
struct ID3D12DescriptorHeap;
struct ID3D12Resource;
class Allocator;

class List
{
public:
	// コンストラクタ
	List(std::weak_ptr<Allocator>allo, const D3D12_COMMAND_LIST_TYPE& type);
	// デストラクタ
	~List();

	// ビューポートセット
	void Viewport(const Vec2& size);

	// シザーセット
	void Scissor(const Vec2& size);

	// バリアセット
	void Barrier(ID3D12Resource* rsc, const D3D12_RESOURCE_STATES& befor, const D3D12_RESOURCE_STATES& affter);

	// グラフィックルートテーブルセット
	void SetGraphicsTable(const unsigned int& id, ID3D12DescriptorHeap* heap, const size_t& index = 0);

	// コンピュートルートテーブルセット
	void SetComputeTable(const unsigned int& id, ID3D12DescriptorHeap* heap, const size_t& index = 0);

	// コマンドリスト取得
	ID3D12GraphicsCommandList5* Get(void) const;

private:
	// コマンドリスト生成
	void CreateList(const D3D12_COMMAND_LIST_TYPE& type);


	// アロケータ
	std::weak_ptr<Allocator>allo;

	// コマンドリスト
	Microsoft::WRL::ComPtr<ID3D12GraphicsCommandList5>list;
};
