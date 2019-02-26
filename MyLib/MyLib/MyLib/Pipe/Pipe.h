#pragma once
#include "../etc/Define.h"
#include <memory>

class Root;

// パイプライン
class Pipe
{
public:
	// コンストラクタ
	Pipe(std::weak_ptr<Root>root, const D3D12_INPUT_ELEMENT_DESC& input, const size_t& num, const D3D12_PRIMITIVE_TOPOLOGY_TYPE& type, const bool& depth);
	Pipe(std::weak_ptr<Root>root);
	// デストラクタ
	~Pipe();

	// パイプライン取得
	ID3D12PipelineState* Get(void) const;

private:
	Pipe(const Pipe&) = delete;
	void operator=(const Pipe&) = delete;

	// 描画用パイプライン生成
	long Graphic(const D3D12_INPUT_ELEMENT_DESC& input, const size_t& num, const D3D12_PRIMITIVE_TOPOLOGY_TYPE& type, const bool& depth);

	// 計算用パイプライン生成
	long Compute(void);


	// ルート
	std::weak_ptr<Root>root;

	// パイプライン
	ID3D12PipelineState* pipe;
};
