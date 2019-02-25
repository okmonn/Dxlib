#pragma once
#include "../Vector/Vector3.h"
#include "../etc/Define.h"

class MyLib;

class WVP
{
	friend MyLib;

	// 定数
	struct Constant {
		//ワールド
		DirectX::XMFLOAT4X4 world;
		//ビュー
		DirectX::XMFLOAT4X4 view;
		//プロジェクション
		DirectX::XMFLOAT4X4 projection;
	};

public:
	// コンストラクタ
	WVP();
	// デストラクタ
	~WVP();

	// カメラセット
	void SetCamera(const Vec3f& pos, const Vec3f& target, const Vec3f& upper, const Vec2f& winSize, const float& fov);

private:
	// 初期化
	void Init(void);

	// カメラ行列セット
	void SetCamera(void);


	// ヒープ
	ID3D12DescriptorHeap* heap;

	// リソース
	ID3D12Resource* rsc;
	
	// 定数データ
	Constant* constant;

	// 座標
	Vec3f pos;

	// ターゲット
	Vec3f target;

	// 向き
	Vec3f upper;

	// ウィンドウサイズ
	Vec2f winSize;

	// 画角
	float fov;
};
