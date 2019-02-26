#pragma once
#include "../etc/Define.h"
#include <string>
#include <memory>
#include <unordered_map>

// テクスチャローダー
class TexLoader
{
public:
	// デストラクタ
	~TexLoader();

	// 読み込み
	long Load(const std::string& fileName);

	// データ削除
	void Delete(const std::string& fileName);

	// インスタンス変数取得
	static TexLoader& Get(void);
	// リソース取得
	ID3D12Resource* GetRsc(const std::string& fileName);
	// デコード取得
	uchar* GetDecode(const std::string& fileName);
	// サブデータ取得
	D3D12_SUBRESOURCE_DATA GetSub(const std::string& fileName);
	// 画像サイズ取得
	Vec2f GetSize(const std::string& fileName);

private:
	TexLoader();
	TexLoader(const TexLoader&) = delete;
	void operator=(const TexLoader&) = delete;


	// リソース
	std::unordered_map<std::string, ID3D12Resource*>rsc;

	// デコード
	std::unordered_map<std::string, std::unique_ptr<uchar[]>>decode;

	// サブデータ
	std::unordered_map<std::string, D3D12_SUBRESOURCE_DATA>sub;
};
