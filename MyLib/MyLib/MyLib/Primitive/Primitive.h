#pragma once
#include "../Vector/Vector3.h"
#include "../etc/Define.h"
#include <vector>

class Primitive
{
public:
	// コンストラクタ
	Primitive();
	// デストラクタ
	~Primitive();

private:
	// ヒープ
	ID3D12DescriptorHeap* heap;

	// 定数リソース
	ID3D12Resource* cRsc;

	// 頂点リソース
	ID3D12Resource* vRsc;
};
