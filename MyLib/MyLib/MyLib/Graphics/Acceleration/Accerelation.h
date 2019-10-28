#pragma once
#include <wrl.h>
#include <array>
#include <memory>

enum D3D12_RESOURCE_STATES : int;
enum D3D12_RESOURCE_FLAGS : int;
struct D3D12_HEAP_PROPERTIES;
struct ID3D12Resource;
class List;

class Acceleration
{
public:
	// コンストラクタ
	Acceleration(std::weak_ptr<List>list, Acceleration* bottom = nullptr);
	// デストラクタ
	~Acceleration();

	// リソース取得
	ID3D12Resource* Get(void) const;

private:
	// リソース生成
	void CreateRsc(const unsigned int& id, const size_t& size, const D3D12_HEAP_PROPERTIES& prop, const D3D12_RESOURCE_STATES& state, const D3D12_RESOURCE_FLAGS& flag);

	// トップレベル構造生成
	void CreateTop(Acceleration* bottom);

	// ボトムレベル構造生成
	void CreateBottom(ID3D12Resource* vertex, const size_t& stride);

	
	// リスト
	std::weak_ptr<List>list;

	// リザルトサイズ
	unsigned __int64 tlasSize;

	// リソース
	std::array<Microsoft::WRL::ComPtr<ID3D12Resource>, 3>rsc;
};
