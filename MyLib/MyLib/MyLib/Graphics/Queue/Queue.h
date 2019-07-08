#pragma once
#include <wrl.h>

enum D3D12_COMMAND_LIST_TYPE : int;
struct ID3D12CommandQueue;

class Queue
{
public:
	// コンストラクタ
	Queue(const D3D12_COMMAND_LIST_TYPE& type);
	// デストラクタ
	~Queue();

	// コマンドキュー取得
	ID3D12CommandQueue* Get(void) const;

private:
	// コマンドキュー生成
	void CreateQueue(const D3D12_COMMAND_LIST_TYPE& type);


	// コマンドキュー
	Microsoft::WRL::ComPtr<ID3D12CommandQueue>queue;
};
