#pragma once
#include "../etc/Define.h"
#include <tuple>
#include <string>
#include <vector>
#include <memory>

// シェーダ情報
struct Blob {
	//データ
	std::vector<uchar>data;
	//サイズ
	size_t size;
};

// ルートシグネチャ
class Root
{
public:
	// コンストラクタ
	Root();
	// デストラクタ
	~Root();

	// 頂点シェーダコンパイル
	void Vertex(const std::string& fileName, const std::string& func = "VS", const std::string& ver = "vs_5_1");
	// ジオメトリーシェーダコンパイル
	void Geometry(const std::string& fileName, const std::string& func = "GS", const std::string& ver = "gs_5_1");
	// ピクセルシェーダコンパイル
	void Pixel(const std::string& fileName, const std::string& func = "PS", const std::string& ver = "ps_5_1");
	// コンピュートシェーダコンパイル
	void Compute(const std::string& fileName, const std::string& func = "CS", const std::string& ver = "cs_5_1");

	// ルートシグネチャ取得
	ID3D12RootSignature* Get(void) const;
	// シグネチャ取得
	ID3DBlob* GetSig(void) const;
	// 頂点シェーダ取得
	std::tuple<ID3DBlob*, std::shared_ptr<Blob>> GetVertex(void) const;
	// ジオメトリーシェーダ取得
	std::tuple<ID3DBlob*, std::shared_ptr<Blob>> GetGeometry(void) const;
	// ピクセルシェーダ取得
	std::tuple<ID3DBlob*, std::shared_ptr<Blob>> GetPixel(void) const;
	// コンピュートシェーダ取得
	std::tuple<ID3DBlob*, std::shared_ptr<Blob>> GetCompute(void) const;

private:
	Root(const Root&) = delete;
	void operator=(const Root&) = delete;

	// シェーダコンパイル
	long Compile(const std::string& fileName, const std::string& func, const std::string& ver, ID3DBlob** blob);

	// .cso読み込み
	int Load(const std::string& fileName, std::shared_ptr<Blob>blob);

	// ルート情報取得
	long RootInfo(ID3DBlob* blob);
	long RootInfo(std::shared_ptr<Blob> blob);

	// ルートシグネチャ生成
	long CreateRoot(void);


	// ルート
	ID3D12RootSignature* root;

	// シグネチャ
	ID3DBlob* sig;

	// 頂点シェーダ
	ID3DBlob* vertex;
	std::shared_ptr<Blob>vBlob;

	// ジオメトリーシェーダー
	ID3DBlob* geometry;
	std::shared_ptr<Blob>gBlob;

	// ピクセルシェーダ
	ID3DBlob* pixel;
	std::shared_ptr<Blob>pBlob;

	// コンピュートシェーダ
	ID3DBlob* compute;
	std::shared_ptr<Blob>cBlob;
};
