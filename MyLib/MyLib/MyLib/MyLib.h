#pragma once
#include "Primitive/Primitive.h"
#include "Texture/Texture.h"
#include "etc/Func.h"
#include <unordered_map>

class Window;
class Queue;
class List;
class Fence;
class Swap;
class Render;
class Depth;
class Root;
class Pipe;

class MyLib
{
	// 定数
	struct Constant {
		//カラー
		Vec3f color;
		//アルファ値
		float alpha;
		//ウィンドウサイズ
		Vec2f winSize;
	};

public:
	// コンストラクタ
	MyLib(const Vec2& size, const Vec2& pos = 0x80000000);
	// デストラクタ
	~MyLib();

	// メッセージの確認
	bool CheckMsg(void) const;

	// クリア
	void Clear(void) const;

	// プリミティブ描画
	void Draw(Primitive& primitive, const Vec3f& color, const float& alpha = 1.0f);

	// 画像描画
	void Draw(Texture& tex, const float& alpha = 1.0f);

	// 実行
	void Execution(void) const;

private:
	//代入禁止
	void operator=(const MyLib&) = delete;

	// 初期化
	void Init(void);

	// ルートのインスタンス
	void RootSignature(const std::string& name, const std::string& fileName);

	// パイプのインスタンス
	void PipeLine(const std::string& name, const std::string& root, 
		const D3D12_PRIMITIVE_TOPOLOGY_TYPE& type, const std::initializer_list<uint>& index, const bool& depth);

	// クラスのインスタンス化
	void Instance(const Vec2& pos);


	// ヒープ
	ID3D12DescriptorHeap* heap;

	// リソース
	ID3D12Resource* rsc;

	// 定数データ
	Constant* constant;

	// ウィンドウ
	std::shared_ptr<Window>win;

	// キュー
	std::shared_ptr<Queue>queue;

	// リスト
	std::shared_ptr<List>list;

	// フェンス
	std::unique_ptr<Fence>fence;

	// スワップ
	std::shared_ptr<Swap>swap;

	// レンダー
	std::unique_ptr<Render>render;

	// デプス
	std::unique_ptr<Depth>depth;

	// ルート
	static std::unordered_map<std::string, std::shared_ptr<Root>>root;

	// パイプ
	static std::unordered_map<std::string, std::shared_ptr<Pipe>>pipe;
};
