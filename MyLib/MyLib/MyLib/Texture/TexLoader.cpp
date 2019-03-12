#include "TexLoader.h"
#include "WICTextureLoader12.h"
#include "../etc/Func.h"
#include "../etc/Release.h"

// コンストラクタ
TexLoader::TexLoader()
{
}

// デストラクタ
TexLoader::~TexLoader()
{
	for (auto& i : rsc)
	{
		Release(i.second);
	}
	for (auto& i : decode)
	{
		i.second.release();
	}
}

// 読み込み
long TexLoader::Load(const std::string & fileName)
{
	if (rsc.find(fileName) != rsc.end())
	{
		return S_OK;
	}

	sub[fileName] = std::make_shared<D3D12_SUBRESOURCE_DATA>();
	auto hr = DirectX::LoadWICTextureFromFile(Dev, func::ChangeCode(fileName).c_str(), &rsc[fileName], decode[fileName], *sub[fileName]);
	if (FAILED(hr))
	{
		func::DebugLog("画像読み込み：失敗");
	}

	return hr;
}

// データ削除
void TexLoader::Delete(const std::string & fileName)
{
	if (rsc.find(fileName) != rsc.end())
	{
		rsc.erase(rsc.find(fileName));
		decode.erase(decode.find(fileName));
		sub.erase(sub.find(fileName));
	}
}

// インスタンス変数取得
TexLoader & TexLoader::Get(void)
{
	static TexLoader instance;
	return instance;
}

// リソース取得
ID3D12Resource * TexLoader::GetRsc(const std::string & fileName)
{
	if (rsc.find(fileName) == rsc.end())
	{
		return nullptr;
	}

	return rsc[fileName];
}

// デコード取得
uchar * TexLoader::GetDecode(const std::string & fileName)
{
	if (decode.find(fileName) == decode.end())
	{
		return nullptr;
	}

	return decode[fileName].get();
}

// サブデータ取得
std::shared_ptr<D3D12_SUBRESOURCE_DATA> TexLoader::GetSub(const std::string & fileName)
{
	if (sub.find(fileName) == sub.end())
	{
		return nullptr;
	}
	
	return sub[fileName];
}

// 画像サイズ取得
Vec2f TexLoader::GetSize(const std::string & fileName)
{
	if (rsc.find(fileName) == rsc.end())
	{
		return Vec2f();
	}

	return Vec2f(float(rsc[fileName]->GetDesc().Width), float(rsc[fileName]->GetDesc().Height));
}
