#include "Root.h"
#include "../Device/Device.h"
#include "../../Func/Func.h"
#include <d3dcompiler.h>
#include <d3d12.h>
#include <crtdbg.h>
#include <functional>
#include <unordered_map>
#include <dxcapi.h>

// シェーダコンパイル
void okmonn::ShaderCompile(const std::string& fileName, const std::string& func, const std::string& ver, ID3DBlob** blob)
{
	auto path = okmonn::ChangeCode(fileName);
	auto f = okmonn::ChangeCode(func);
	auto v = okmonn::ChangeCode(ver);
	Microsoft::WRL::ComPtr<IDxcCompiler>compiler = nullptr;
	auto hr = DxcCreateInstance(__uuidof(compiler), IID_PPV_ARGS(&compiler));
	_ASSERT(hr == S_OK);

	Microsoft::WRL::ComPtr<IDxcBlob>b = nullptr;
	
	LPCWSTR arg[] = { L"/Zi" };
	Microsoft::WRL::ComPtr<IDxcOperationResult>result = nullptr;
	hr = compiler->Compile(b.Get(), path.c_str(), f.c_str(), v.c_str(), arg, _countof(arg), nullptr, 0, nullptr, &result);
	_ASSERT(hr == S_OK);

	/*auto hr = D3DCompileFromFile(path.c_str(), nullptr, D3D_COMPILE_STANDARD_FILE_INCLUDE, func.c_str(), ver.c_str(),
		D3DCOMPILE_DEBUG | D3DCOMPILE_SKIP_OPTIMIZATION, 0, *(&blob), nullptr);
	*/_ASSERT(hr == S_OK);
}

// .cso読み込み
void okmonn::ShaderLoad(const std::string& fileName, ID3DBlob** blob)
{
	auto path = okmonn::ChangeCode(fileName);
	auto hr = D3DReadFileToBlob(path.c_str(), blob);
	_ASSERT(hr == S_OK);
}

// リソース読み込み
void okmonn::ShaderRead(const int& id, ID3DBlob** blob)
{
	HRSRC rsc = FindResource(nullptr, MAKEINTRESOURCE(id), L"Shader");
	_ASSERT(rsc != nullptr);

	HANDLE handle = LoadResource(nullptr, rsc);
	_ASSERT(handle != nullptr);

	void* data = LockResource(handle);
	size_t size = SizeofResource(nullptr, rsc);

	auto hr = D3DSetBlobPart(data, size, D3D_BLOB_PART::D3D_BLOB_PRIVATE_DATA, 0, data, size, blob);
	_ASSERT(hr == S_OK);
}

// コンストラクタ
Root::Root() :
	root(nullptr), vertex(nullptr), geometry(nullptr), pixel(nullptr), compute(nullptr)
{
}

// デストラクタ
Root::~Root()
{
}

// ルートシグネチャ生成
void Root::CreateRoot(ID3DBlob* blob)
{
	Microsoft::WRL::ComPtr<ID3DBlob>sig = nullptr;
	auto hr = D3DGetBlobPart(blob->GetBufferPointer(), blob->GetBufferSize(), D3D_BLOB_PART::D3D_BLOB_ROOT_SIGNATURE, 0, &sig);
	_ASSERT(hr == S_OK);

	hr = Device::Get().Dev()->CreateRootSignature(0, sig->GetBufferPointer(), sig->GetBufferSize(), IID_PPV_ARGS(&root));
	_ASSERT(hr == S_OK);
}

// 頂点シェーダコンパイル
void Root::Vertex(const std::string& fileName, const std::string& func, const std::string& ver)
{
	okmonn::ShaderCompile(fileName, func, ver, &vertex);
	CreateRoot(vertex.Get());
}

// ジオメトリーシェーダコンパイル
void Root::Geometry(const std::string& fileName, const std::string& func, const std::string& ver)
{
	okmonn::ShaderCompile(fileName, func, ver, &geometry);
}

// ピクセルシェーダコンパイル
void Root::Pixel(const std::string& fileName, const std::string& func, const std::string& ver)
{
	okmonn::ShaderCompile(fileName, func, ver, &pixel);
}

// コンピュートシェーダコンパイル
void Root::Compute(const std::string& fileName, const std::string& func, const std::string& ver)
{
	okmonn::ShaderCompile(fileName, func, ver, &compute);
	CreateRoot(compute.Get());
}

// 頂点シェーダの.cso読み込み
void Root::Vertex(const std::string& fileName)
{
	okmonn::ShaderLoad(fileName, &vertex);
	CreateRoot(vertex.Get());
}

// ジオメトリシェーダの.cso読み込み
void Root::Geometry(const std::string& fileName)
{
	okmonn::ShaderLoad(fileName, &geometry);
}

// ピクセルシェーダの.cso読み込み
void Root::Pixel(const std::string& fileName)
{
	okmonn::ShaderLoad(fileName, &pixel);
}

// コンピュートシェーダの.cso読み込み
void Root::Compute(const std::string& fileName)
{
	okmonn::ShaderLoad(fileName, &compute);
	CreateRoot(compute.Get());
}

// 頂点シェーダのリソース読み込み
void Root::Vertex(const int& id)
{
	okmonn::ShaderRead(id, &vertex);
	CreateRoot(vertex.Get());
}

// ジオメトリシェーダのリソース読み込み
void Root::Geometry(const int& id)
{
	okmonn::ShaderRead(id, &geometry);
}

// ピクセルシェーダのリソース読み込み
void Root::Pixel(const int& id)
{
	okmonn::ShaderRead(id, &pixel);
}

// コンピュートシェーダのリソース読み込み
void Root::Compute(const int& id)
{
	okmonn::ShaderRead(id, &compute);
	CreateRoot(compute.Get());
}

// ルートシグネチャ取得
ID3D12RootSignature* Root::Get(void) const
{
	return root.Get();
}

// 頂点シェーダ情報取得
ID3DBlob* Root::GetVertex(void) const
{
	return vertex.Get();
}

// ジオメトリシェーダ情報取得
ID3DBlob* Root::GetGeometry(void) const
{
	return geometry.Get();
}

// ピクセルシェーダ情報取得
ID3DBlob* Root::GetPixel(void) const
{
	return pixel.Get();
}

// コンピュートシェーダ情報取得
ID3DBlob* Root::GetCompute(void) const
{
	return compute.Get();
}
