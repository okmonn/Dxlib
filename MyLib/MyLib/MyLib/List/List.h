#pragma once
#include "../Vector/Vector2.h"
#include "../etc/Define.h"

class List
{
public:
	// コンストラクタ
	List(const D3D12_COMMAND_LIST_TYPE& type);
	// デストラクタ
	~List();

	// リセット
	void Reset(ID3D12PipelineState* pipe = nullptr) const;

	// ビューポートセット
	void Viewport(const Vec2& size) const;

	// シザーセット
	void Scissor(const Vec2& size) const;

	// バリアセット
	void Barrier(const D3D12_RESOURCE_STATES& befor, const D3D12_RESOURCE_STATES& affter, ID3D12Resource* rsc) const;

	// 描画用ルートセット
	void GraphicRoot(ID3D12RootSignature* root) const;

	// 計算用ルートセット
	void ComputeRoot(ID3D12RootSignature* root) const;

	// パイプラインセット
	void Pipeline(ID3D12PipelineState* pipe) const;

	// ヒープセット
	void Heap(ID3D12DescriptorHeap** heap, const size_t& num) const;

	// 描画用ルートとヒープ関連付け
	void GraphicTable(const uint& id, ID3D12DescriptorHeap* heap, const uint& index = 0) const;

	// 計算用ルートとヒープ関連付け
	void ComputeTable(const uint& id, ID3D12DescriptorHeap* heap, const uint& index = 0) const;

	// 頂点バッファビューセット
	void VertexView(const D3D12_VERTEX_BUFFER_VIEW& view) const;

	// インデックスバッファビューセット
	void IndexView(const D3D12_INDEX_BUFFER_VIEW& view) const;

	// トポロジーセット
	void Topology(const D3D_PRIMITIVE_TOPOLOGY& type) const;

	// 頂点描画
	void DrawVertex(const size_t& num, const uint& instance = 1) const;

	// バンドル実行
	void Bundle(ID3D12GraphicsCommandList* list) const;

	// GPU計算実行
	void Dispatch(const uint& x, const uint& y, const uint& z) const;

	// クローズ
	void Close(void) const;

	// アロケータ取得
	ID3D12CommandAllocator* GetAllo(void) const;
	// リスト取得
	ID3D12GraphicsCommandList* GetList(void) const;

private:
	// アロケータ生成
	long CreateAllo(const D3D12_COMMAND_LIST_TYPE& type);

	// リスト生成
	long CreateList(const D3D12_COMMAND_LIST_TYPE& type);

	// 初期化
	void Init(const D3D12_COMMAND_LIST_TYPE& type);

	
	// アロケータ
	ID3D12CommandAllocator* allo;

	// リスト
	ID3D12GraphicsCommandList* list;
};
