#pragma once
#include <wrl.h>
#include <string>

struct ID3D12RootSignature;
struct ID3D10Blob;
typedef ID3D10Blob ID3DBlob;

namespace okmonn
{
	// シェーダコンパイル
	void ShaderCompile(const std::string& fileName, const std::string& func, const std::string& ver, ID3DBlob** blob);

	// .cso読み込み
	void ShaderLoad(const std::string& fileName, ID3DBlob** blob);

	// リソース読み込み
	void ShaderRead(const int& id, ID3DBlob** blob);
}

class Root
{
public:
	// コンストラクタ
	Root();
	// デストラクタ
	~Root();

	// シェーダコンパイル
	void Vertex(const std::string& fileName, const std::string& func, const std::string& ver);
	void Geometry(const std::string& fileName, const std::string& func, const std::string& ver);
	void Pixel(const std::string& fileName, const std::string& func, const std::string& ver);
	void Compute(const std::string& fileName, const std::string& func, const std::string& ver);

	// .cso読み込み
	void Vertex(const std::string& fileName);
	void Geometry(const std::string& fileName);
	void Pixel(const std::string& fileName);
	void Compute(const std::string& fileName);

	// リソース読み込み
	void Vertex(const int& id);
	void Geometry(const int& id);
	void Pixel(const int& id);
	void Compute(const int& id);

	// ルートシグネチャ取得
	ID3D12RootSignature* Get(void) const;

	// 頂点シェーダ情報取得
	ID3DBlob* GetVertex(void) const;

	// ジオメトリシェーダ情報取得
	ID3DBlob* GetGeometry(void) const;

	// ピクセルシェーダ情報取得
	ID3DBlob* GetPixel(void) const;

	// コンピュートシェーダ情報取得
	ID3DBlob* GetCompute(void) const;

private:
	// ルートシグネチャ生成
	void CreateRoot(ID3DBlob* blob);


	// ルートシグネチャ
	Microsoft::WRL::ComPtr<ID3D12RootSignature>root;

	// 頂点シェーダ
	Microsoft::WRL::ComPtr<ID3DBlob>vertex;

	// ジオメトリシェーダ
	Microsoft::WRL::ComPtr<ID3DBlob>geometry;

	// ピクセルシェーダ
	Microsoft::WRL::ComPtr<ID3DBlob>pixel;

	// コンピュートシェーダ
	Microsoft::WRL::ComPtr<ID3DBlob>compute;
};
