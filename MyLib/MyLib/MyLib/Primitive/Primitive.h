#pragma once
#include "../Vector/Vector3.h"
#include "../etc/Define.h"
#include <vector>

// タイプ
enum class PrimitiveType {
	//ポイント
	point,
	//ライン
	line,
	//トライアングル
	triangle,
	//ボックス
	box
};

class Primitive
{
public:
	// コンストラクタ
	Primitive();
	// デストラクタ
	~Primitive();

	// 初期化
	void Init(const PrimitiveType& type, const uint& num);


	// 頂点データ
	std::vector<Vec3f>pos;

private:
	// リソース
	ID3D12Resource* rsc;

	// タイプ
	int type;
};
