#pragma once
#include "../../etc/Single.h"
#include "../../etc/Vector2.h"
#include <wrl.h>
#include <string>
#include <memory>
#include <unordered_map>

struct D3D12_SUBRESOURCE_DATA;
struct ID3D12Resource;

class TexLoader :
	public Single<TexLoader>
{
	friend Single<TexLoader>;
public:
	// 読み込み
	void Load(const std::string& fileName);

	// データ削除
	void Delete(const std::string& fileName);

	// リソース取得
	ID3D12Resource* Rsc(const std::string& fileName);

	// デコードデータ取得
	unsigned char* Decode(const std::string& fileName);

	// サブデータ取得
	std::shared_ptr<D3D12_SUBRESOURCE_DATA> SubData(const std::string& fileName);

	// 画像サイズ取得
	Vec2f GetSize(const std::string& fileName);

private:
	// コンストラクタ
	TexLoader();
	// デストラクタ
	~TexLoader();


	// リソース
	std::unordered_map<std::string, Microsoft::WRL::ComPtr<ID3D12Resource>>rsc;

	// デコード
	std::unordered_map<std::string, std::unique_ptr<unsigned char[]>>decode;

	// サブデータ
	std::unordered_map<std::string, std::shared_ptr<D3D12_SUBRESOURCE_DATA>>sub;
};
