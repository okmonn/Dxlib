#pragma once
#include <wrl.h>
#include <memory>

enum D3D12_PRIMITIVE_TOPOLOGY_TYPE;
struct ID3D12PipelineState;
struct D3D12_INPUT_ELEMENT_DESC;
class Root;

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
	// パイプライン生成
	void CreatePipe(std::weak_ptr<Root>root, const D3D12_INPUT_ELEMENT_DESC& input, const size_t& num, const D3D12_PRIMITIVE_TOPOLOGY_TYPE& type, const bool& depth);
	void Create(std::weak_ptr<Root>root);

	// パイプライン
	Microsoft::WRL::ComPtr<ID3D12PipelineState>pipe;
};
