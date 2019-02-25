#pragma once
#include "../Vector/Vector3.h"
#include "../etc/Define.h"
#include <vector>

class MyLib;

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
	friend MyLib;
public:
	// 頂点データ
	std::vector<Vec3f>pos;


	// コンストラクタ
	Primitive();
	Primitive(const PrimitiveType& type);
	Primitive(const PrimitiveType& type, const uint& num);
	// コピーコンストラクタ
	Primitive(const Primitive& prim);
	// デストラクタ
	~Primitive();

	// 初期化
	void Init(const PrimitiveType& type, const uint& num);

	// 演算子オーバーロード
	void operator=(const Primitive& prim);

private:
	// データ更新
	void UpData(void) const;


	// リソース
	ID3D12Resource* rsc;

	// 送信データ
	void* data;

	// タイプ
	int type;
};
