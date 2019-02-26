#pragma once
#include "../etc/Define.h"
#include <string>
#include <vector>
#include <memory>

class List;
class MyLib;

// 頂点情報
struct Vertex {
	//座標
	Vec3f pos;
	//UV
	Vec2f uv;
};

// テクスチャ
class Texture
{
	friend MyLib;

	// 定数
	struct Constant {
		//行列
		DirectX::XMFLOAT4X4 matrix;
		//UV座標
		Vec2f uvPos;
		//UVサイズ
		Vec2f uvSize;
		//反転
		Vec2f reverse;
	};

public:
	// 座標
	Vec3f pos;

	// サイズ
	Vec2f size;

	// UV座標
	Vec2f uvPos;

	// UVサイズ
	Vec2f uvSize;

	// 回転
	float rotate;

	// 反転フラグ
	Vec2 reverse;

	// コンストラクタ
	Texture();
	Texture(const std::string& fileName);
	// コピーコンストラクタ
	Texture(const Texture& tex);
	// デストラクタ
	~Texture();

	// 読み込み
	int Load(const std::string& fileName);

	// テクスチャサイズ取得
	Vec2f GetTexSize(void) const;

	// 演算子オーバーロード
	void operator=(const Texture& tex);

private:
	// 定数リソース生成
	long CreateConstant(void);

	// 頂点リソース生成
	long CreateVertex(void);

	// サブリソース書き込み
	long WriteSub(const uint& index);

	// 初期化
	void Init(void);

	// 描画準備
	uint SetDraw(std::weak_ptr<List>list);

	// 頂点数取得
	uint GetVertexNum(void) const;

	// ヒープ
	ID3D12DescriptorHeap* heap;

	// リソース
	std::vector<ID3D12Resource*>rsc;

	// 行列
	Constant* constant;

	// 頂点送信データ
	void* data;

	// ファイル名
	std::string fileName;

	// 頂点情報
	static std::vector<Vertex>vertex;
};
