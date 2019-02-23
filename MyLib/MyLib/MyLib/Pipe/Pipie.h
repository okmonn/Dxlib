#pragma once
#include "../etc/Define.h"
#include <memory>

class Root;

class Pipe
{
public:
	// コンストラクタ
	Pipe(std::weak_ptr<Root>root);
	// デストラクタ
	~Pipe();

	// 描画用パイプライン生成
	long Graphic(const D3D12_INPUT_ELEMENT_DESC& input, const size_t& num, const D3D12_PRIMITIVE_TOPOLOGY_TYPE& type, const bool& depth);

	// 計算用パイプライン生成
	long Compute(void);

	// パイプライン取得
	ID3D12PipelineState* Get(void) const;

private:
	// ルート
	std::weak_ptr<Root>root;

	// パイプライン
	ID3D12PipelineState* pipe;
};
