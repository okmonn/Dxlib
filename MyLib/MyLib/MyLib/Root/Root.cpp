#include <d3dcompiler.h>
#include "Root.h"
#include "../etc/Release.h"

// コンストラクタ
Root::Root(const std::wstring & fileName) : 
	root(nullptr), sig(nullptr), vertex(nullptr), geometry(nullptr), pixel(nullptr), compute(nullptr)
{
	Init(fileName);
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

// シェーダコンパイル
long Root::Compile(const std::wstring & fileName)
{
	auto hr = D3DCompileFromFile(fileName.c_str(), nullptr, D3D_COMPILE_STANDARD_FILE_INCLUDE, "VS", "vs_5_1", D3DCOMPILE_DEBUG | D3DCOMPILE_SKIP_OPTIMIZATION, 0, &vertex, nullptr);
	if (FAILED(hr))
	{
		hr = D3DCompileFromFile(fileName.c_str(), nullptr, D3D_COMPILE_STANDARD_FILE_INCLUDE, "CS", "cs_5_1", D3DCOMPILE_DEBUG | D3DCOMPILE_SKIP_OPTIMIZATION, 0, &compute, nullptr);
		if (hr == S_OK)
		{
			OutputDebugString(_T("\nコンピュートシェーダ読み込み：成功\n"));
			return hr;
		}
		OutputDebugString(_T("\n頂点シェーダ読み込み：失敗\n"));
		return hr;
	}

	hr = D3DCompileFromFile(fileName.c_str(), nullptr, D3D_COMPILE_STANDARD_FILE_INCLUDE, "GS", "gs_5_1", D3DCOMPILE_DEBUG | D3DCOMPILE_SKIP_OPTIMIZATION, 0, &geometry, nullptr);
	if (FAILED(hr))
	{
		OutputDebugString(_T("\nジオメトリシェーダ読み込み：失敗\n"));
		OutputDebugString(_T("ジオメトリシェーダを使用していない場合は無視してOK\n"));
	}

	hr = D3DCompileFromFile(fileName.c_str(), nullptr, D3D_COMPILE_STANDARD_FILE_INCLUDE, "PS", "ps_5_1", D3DCOMPILE_DEBUG | D3DCOMPILE_SKIP_OPTIMIZATION, 0, &pixel, nullptr);
	if (FAILED(hr))
	{
		OutputDebugString(_T("\nピクセルシェーダ読み込み：失敗\n"));
		return hr;
	}

	return hr;
}

// ルート情報取得
long Root::RootInfo(void)
{
	auto hr = S_OK;
	if (vertex != nullptr)
	{
		hr = D3DGetBlobPart(vertex->GetBufferPointer(), vertex->GetBufferSize(), D3D_BLOB_PART::D3D_BLOB_ROOT_SIGNATURE, 0, &sig);
	}
	else
	{
		hr = D3DGetBlobPart(compute->GetBufferPointer(), compute->GetBufferSize(), D3D_BLOB_PART::D3D_BLOB_ROOT_SIGNATURE, 0, &sig);
	}
	if (FAILED(hr))
	{
		OutputDebugString(_T("\nルートシグネチャ情報取得：失敗\n"));
	}

	return hr;
}

// ルートシグネチャ生成
long Root::CreateRoot(void)
{
	auto hr = Dev->CreateRootSignature(0, sig->GetBufferPointer(), sig->GetBufferSize(), IID_PPV_ARGS(&root));
	if (FAILED(hr))
	{
		OutputDebugString(_T("\nルートシグネチャ生成：失敗\n"));
	}

	return hr;
}

// 初期化
void Root::Init(const std::wstring & fileName)
{
	Compile(fileName);
	RootInfo();
	CreateRoot();
}

// ルートシグネチャ取得
ID3D12RootSignature * Root::Get(void) const
{
	return root;
}

// シグネチャ取得
ID3DBlob * Root::GetSig(void) const
{
	return sig;
}

// 頂点シェーダ取得
ID3DBlob * Root::GetVertex(void) const
{
	return vertex;
}

// ジオメトリーシェーダ取得
ID3DBlob * Root::GetGeometry(void) const
{
	return geometry;
}

// ピクセルシェーダ取得
ID3DBlob * Root::GetPixel(void) const
{
	return pixel;
}

// コンピュートシェーダ取得
ID3DBlob * Root::GetCompute(void) const
{
	return compute;
}
