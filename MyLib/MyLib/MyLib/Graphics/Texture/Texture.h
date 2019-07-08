#pragma once
#include "../../etc/Vector3.h"
#include <wrl.h>
#include <string>
#include <vector>
#include <memory>

struct ID3D12DescriptorHeap;
struct ID3D12Resource;
class List;

class Texture
{
	// 頂点情報
	struct Vertex {
		//座標
		Vec3f pos;
		//UV
		Vec2f uv;
	};

	// 定数情報
	struct Constant {
		//画像サイズ
		Vec2f size;
		//反転
		Vec2f reverse;
		//角度
		float angle;
		//透明率
		float alpha;
	};

	// リソース
	struct Resource {
		//インデックス
		unsigned char index;
		//リソース
		Microsoft::WRL::ComPtr<ID3D12Resource>rsc;

		Resource() : index(0), rsc(nullptr){}
	};

public:
	// コンストラクタ
	Texture();
	Texture(const std::string& fileName);
	// デストラクタ
	~Texture();

	// 読み込み
	void Load(const std::string& fileName);

	// 本来のサイズで描画
	void DrawImg(const Vec2f& pos, const float& angle, const bool& turnX, const bool& turnY, const float& alpha);

	// 指定したサイズで描画
	void DrawRect(const Vec2f& pos, const Vec2f& size, const float& angle, const bool& turnX, const bool& turnY, const float& alpha);

	// 指定したサイズで分割描画
	void DrawDivide(const Vec2f& pos, const Vec2f& size, const Vec2f& uvPos, const Vec2f& uvSize, 
		const float& angle, const bool& turnX, const bool& turnY, const float& alpha);

	// 描画
	void Draw(std::weak_ptr<List>list);

private:
	// 初期化
	void Init(void);

	// 頂点リソース生成
	void CreateVRsc(void);

	// 定数リソース生成
	void CreateCRsc(void);


	// ヒープ
	Microsoft::WRL::ComPtr<ID3D12DescriptorHeap>heap;

	// 頂点リソース
	Microsoft::WRL::ComPtr<ID3D12Resource>vRsc;

	// 頂点送信データ
	void* data;

	// 定数リソース
	Resource cRsc;

	// 定数情報
	Constant* constant;

	// インデックス
	unsigned char index;

	// 頂点情報
	std::vector<Vertex>vertex;
};
