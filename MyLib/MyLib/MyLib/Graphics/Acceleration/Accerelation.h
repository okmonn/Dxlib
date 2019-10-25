#pragma once
#include <wrl.h>
#include <array>
#include <memory>

struct ID3D12Resource;
class List;

class Acceleration
{
public:
	// コンストラクタ
	Acceleration(std::weak_ptr<List>list);
	// デストラクタ
	~Acceleration();

private:
	// トップレベル構造生成
	void CreateTop(void);

	// ボトムレベル構造生成
	void CreateBottom(ID3D12Resource* vertex, const size_t& stride);

	
	// リスト
	std::weak_ptr<List>list;

	// リソース
	std::array<Microsoft::WRL::ComPtr<ID3D12Resource>, 3>rsc;
};
