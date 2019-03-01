#include <d3dcompiler.h>
#include "Root.h"
#include "../etc/Func.h"
#include "../etc/Release.h"
#include <iostream>

// コンストラクタ
Root::Root() : 
	root(nullptr), sig(nullptr), vertex(nullptr), geometry(nullptr), pixel(nullptr), compute(nullptr)
{
	vBlob = {};
	gBlob = {};
	pBlob = {};
	cBlob = {};
}

// デストラクタ
Root::~Root()
{
	Release(compute);
	Release(pixel);
	Release(geometry);
	Release(vertex);
	Release(sig);
	Release(root);
}

// 頂点シェーダコンパイル
void Root::Vertex(const std::string& fileName, const std::string& func, const std::string& ver)
{
	if (fileName.find(".hlsl") != std::string::npos)
	{
		Compile(fileName, func, ver, &vertex);
		RootInfo(vertex);
	}
	else if (fileName.find(".cso") != std::string::npos)
	{
		vBlob = std::make_shared<Blob>();
		Load(fileName, vBlob);
		RootInfo(vBlob);
	}
	else
	{

	}
	
	CreateRoot();
}

// ジオメトリーシェーダコンパイル
void Root::Geometry(const std::string & fileName, const std::string & func, const std::string & ver)
{
	if (fileName.find(".hlsl") != std::string::npos)
	{
		Compile(fileName, func, ver, &geometry);
	}
	else if (fileName.find(".cso") != std::string::npos)
	{
		gBlob = std::make_shared<Blob>();
		Load(fileName, gBlob);
	}
	else
	{

	}
}

// ピクセルシェーダコンパイル
void Root::Pixel(const std::string & fileName, const std::string & func, const std::string & ver)
{
	if (fileName.find(".hlsl") != std::string::npos)
	{
		Compile(fileName, func, ver, &pixel);
	}
	else if (fileName.find(".cso") != std::string::npos)
	{
		pBlob = std::make_shared<Blob>();
		Load(fileName, pBlob);
	}
	else
	{

	}
}

// コンピュートシェーダコンパイル
void Root::Compute(const std::string & fileName, const std::string & func, const std::string & ver)
{
	if (fileName.find(".hlsl") != std::string::npos)
	{
		Compile(fileName, func, ver, &compute);
		RootInfo(compute);
	}
	else if (fileName.find(".cso") != std::string::npos)
	{
		cBlob = std::make_shared<Blob>();
		Load(fileName, cBlob);
		RootInfo(cBlob);
	}
	else
	{
		
	}
	
	CreateRoot();
}

// シェーダコンパイル
long Root::Compile(const std::string& fileName, const std::string& func, const std::string& ver, ID3DBlob** blob)
{
	auto pass = func::ChangeCode(fileName);
	auto hr = D3DCompileFromFile(pass.c_str(), nullptr, D3D_COMPILE_STANDARD_FILE_INCLUDE, func.c_str(), ver.c_str(),
		D3DCOMPILE_DEBUG | D3DCOMPILE_SKIP_OPTIMIZATION, 0, *(&blob), nullptr);
	if (FAILED(hr))
	{
		func::DebugLog("シェーダコンパイル：失敗");
	}

	return hr;
}

// .cso読み込み
int Root::Load(const std::string& fileName, std::shared_ptr<Blob> blob)
{
	FILE* file = nullptr;
	if (fopen_s(&file, fileName.c_str(), "rb") != 0)
	{
		func::DebugLog(".cso読み込み：失敗");
		return -1;
	}

	//終端に移動
	fseek(file, 0, SEEK_END);
	//サイズ取得
	blob->data.resize(ftell(file));
	blob->size = blob->data.size();
	//先頭に移動
	fseek(file, 0, SEEK_SET);
	fread(blob->data.data(), sizeof(blob->data[0]) * blob->data.size(), 1, file);

	fclose(file);

	return 0;
}

// ルート情報取得
long Root::RootInfo(ID3DBlob* blob)
{
	auto hr = D3DGetBlobPart(blob->GetBufferPointer(), blob->GetBufferSize(), D3D_BLOB_PART::D3D_BLOB_ROOT_SIGNATURE, 0, &sig);
	if (FAILED(hr))
	{
		func::DebugLog("ルートシグネチャ情報取得：失敗");
	}

	return hr;
}

// ルート情報取得
long Root::RootInfo(std::shared_ptr<Blob> blob)
{
	auto hr = D3DGetBlobPart(blob->data.data(), blob->size, D3D_BLOB_PART::D3D_BLOB_ROOT_SIGNATURE, 0, &sig);
	if (FAILED(hr))
	{
		func::DebugLog("ルートシグネチャ情報取得：失敗");
	}

	return hr;
}

// ルートシグネチャ生成
long Root::CreateRoot(void)
{
	auto hr = Dev->CreateRootSignature(0, sig->GetBufferPointer(), sig->GetBufferSize(), IID_PPV_ARGS(&root));
	if (FAILED(hr))
	{
		func::DebugLog("ルートシグネチャ生成：失敗");
	}

	return hr;
}

// ルートシグネチャ取得
ID3D12RootSignature* Root::Get(void) const
{
	return root;
}

// シグネチャ取得
ID3DBlob* Root::GetSig(void) const
{
	return sig;
}

// 頂点シェーダ取得
std::tuple<ID3DBlob*, std::shared_ptr<Blob>> Root::GetVertex(void) const
{
	return std::forward_as_tuple(vertex, vBlob);
}

// ジオメトリーシェーダ取得
std::tuple<ID3DBlob*, std::shared_ptr<Blob>> Root::GetGeometry(void) const
{
	return std::forward_as_tuple(geometry, gBlob);
}

// ピクセルシェーダ取得
std::tuple<ID3DBlob*, std::shared_ptr<Blob>> Root::GetPixel(void) const
{
	return std::forward_as_tuple(pixel, pBlob);
}

// コンピュートシェーダ取得
std::tuple<ID3DBlob*, std::shared_ptr<Blob>> Root::GetCompute(void) const
{
	return std::forward_as_tuple(compute, cBlob);
}
