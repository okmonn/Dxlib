#pragma once
#include "../etc/Define.h"

class Root
{
public:
	// コンストラクタ
	Root(const std::wstring& fileName);
	// デストラクタ
	~Root();

	// ルートシグネチャ取得
	ID3D12RootSignature* Get(void) const;
	// シグネチャ取得
	ID3DBlob* GetSig(void) const;
	// 頂点シェーダ取得
	ID3DBlob* GetVertex(void) const;
	// ジオメトリーシェーダ取得
	ID3DBlob* GetGeometry(void) const;
	// ピクセルシェーダ取得
	ID3DBlob* GetPixel(void) const;
	// コンピュートシェーダ取得
	ID3DBlob* GetCompute(void) const;


private:
	// シェーダコンパイル
	long Compile(const std::wstring& fileName);

	// ルート情報取得
	long RootInfo(void);

	// ルートシグネチャ生成
	long CreateRoot(void);

	// 初期化
	void Init(const std::wstring& fileName);


	// ルート
	ID3D12RootSignature* root;

	// シグネチャ
	ID3DBlob* sig;

	// 頂点シェーダ
	ID3DBlob* vertex;

	// ジオメトリーシェーダー
	ID3DBlob* geometry;

	// ピクセルシェーダ
	ID3DBlob* pixel;

	// コンピュートシェーダ
	ID3DBlob* compute;
};
