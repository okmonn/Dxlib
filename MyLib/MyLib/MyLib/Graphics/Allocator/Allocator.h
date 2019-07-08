#pragma once
#include <wrl.h>

enum D3D12_COMMAND_LIST_TYPE : int;
struct ID3D12CommandAllocator;

class Allocator
{
public:
	// コンストラクタ
	Allocator(const D3D12_COMMAND_LIST_TYPE& type);
	// デストラクタ
	~Allocator();

	// コマンドアロケータ取得
	ID3D12CommandAllocator* Get(void) const;

private:
	// コマンドアロケータ生成
	void CreateAllo(const D3D12_COMMAND_LIST_TYPE& type);


	// コマンドアロケータ
	Microsoft::WRL::ComPtr<ID3D12CommandAllocator>allo;
};
