#pragma once
#include "Input/Input.h"
#include "Primitive/Primitive.h"
#include "Texture/Texture.h"
#include "Sound/Sound.h"
#include "Compute/Compute.h"
#include "etc/Func.h"

#define KEY Input::Get()

class Window;
class Queue;
class List;
class Fence;
class Swap;
class Render;
class Depth;
class Root;
class Pipe;

// おかもん自作ライブラリ
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
	MyLib(const MyLib& mylib, const Vec2& size, const Vec2& pos = 0x80000000);
	MyLib(std::weak_ptr<MyLib> mylib, const Vec2& size, const Vec2& pos = 0x80000000);
	// デストラクタ
	~MyLib();

	// タイトル名変更
	void ChangeTitle(const std::string& title);

	// ドロップされたファイルパス取得
	std::string GetDropFilePass(void);

	// ウィンドウ座標取得
	Vec2 GetWinPos(void);

	// ウィンドウサイズ取得
	Vec2 GetWinSize(void);

	// マウス座標取得
	Vec2 GetMousePos(void);

	// マウスホイール量取得
	int GetMouseWheel(void) const;

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
	MyLib(const MyLib&) = delete;
	void operator=(const MyLib&) = delete;

	// 初期化
	void Init(void);

	// ルートのインスタンス
	template <typename T>
	void RootSignature(const std::string& name, const std::initializer_list<T>& id);

	// パイプのインスタンス
	void PipeLine(const std::string& name, const std::string& root, 
		const D3D12_PRIMITIVE_TOPOLOGY_TYPE& type, const std::initializer_list<uint>& index, const bool& depth);

	// クラスのインスタンス化
	void Instance(const Vec2& pos, void* parent = nullptr);


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
