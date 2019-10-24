#pragma once
#include "../etc/Single.h"
#include "../etc/Vector3.h"
#include <wrl.h>
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>

enum D3D12_PRIMITIVE_TOPOLOGY_TYPE : int;
struct ID3D12DescriptorHeap;
struct ID3D12Resource;
class Window;
class Queue;
class Allocator;
class List;
class Fence;
class Swap;
class Render;
class Root;
class Pipe;
class Texture;
class Primitive;

class MyLib
{
public:
	// コンストラクタ
	MyLib(const Vec2& size, const Vec2& pos, MyLib * parent);
	// デストラクタ
	~MyLib();

	// 画面クリア
	void Clear(void);

	// 実行
	void Execution(void);

	// 描画準備
	void SetDraw(const size_t& index = 0);

	// ウィンドウサイズ取得
	Vec2 GetWinSize(void);

	// コマンドリスト取得
	std::weak_ptr<List>GetList(void) const;

private:
	// 定数リソース生成
	void CreateRsc(void);

	// 初期化
	void Init(void);


	// ウィンドウ
	std::shared_ptr<Window>win;

	// キュー
	std::shared_ptr<Queue>queue;

	// アロケータ
	std::vector<std::shared_ptr<Allocator>>allo;

	// リスト
	std::shared_ptr<List>list;

	// フェンス
	std::shared_ptr<Fence>fence;

	// スワップ
	std::shared_ptr<Swap>swap;

	// レンダー
	std::shared_ptr<Render>render;

	// ヒープ
	Microsoft::WRL::ComPtr<ID3D12DescriptorHeap>heap;

	// リソース
	Microsoft::WRL::ComPtr<ID3D12Resource>rsc;

	// 送信データ
	Vec2f* data;
};

class Manager : 
	public Single<Manager>
{
	friend Single<Manager>;
public:
	// ライブラリ初期化
	bool InitLib(const Vec2& size, const Vec2& pos, const std::string& parent);

	// 画像読み込み
	int LoadImg(const std::string& fileName);

	// 画面クリア
	void Clear(void);

	// 本来の画像サイズで描画
	void DrawImg(const int& id, const Vec2f& pos, const float& angle, const bool& turnX, const bool& turnY, const float& alpha);

	// 指定した画像サイズで描画
	void DrawImgRect(const int& id, const Vec2f& pos, const Vec2f& size, const float& angle, const bool& turnX, const bool& turnY, const float& alpha);

	// 指定した画像サイズで指定した矩形に分割して描画
	void DrawImgDivide(const int& id, const Vec2f& pos, const Vec2f& size, const Vec2f& uvPos, const Vec2f& uvSize, 
		const float& angle, const bool& turnX, const bool& turnY, const float& alpha);

	// ポイント描画
	void DrawPoint(const Vec2f& pos, const float& r, const float& g, const float& b, const float& a);

	// ライン描画
	void DrawLine(const Vec2f& pos1, const Vec2f& pos2, const float& r, const float& g, const float& b, const float& a);

	// トライアングル描画
	void DrawTriangle(const Vec2f& pos1, const Vec2f& pos2, const Vec2f& pos3, const float& r, const float& g, const float& b, const float& a);

	// ボックス描画
	void DrawBox(const Vec2f& pos, const Vec2f& size, const float& r, const float& g, const float& b, const float& a);

	// 実行
	void Execution(void);

	// テクスチャハンドルの削除
	void DeleteTex(const int& id);

	// プリミティブデータの削除
	void DeletePrim(const bool& memReset);

	// ライブラリのターゲット切り替え
	void ChangeTarget(const std::string& name);

	// ライブラリターゲットの取得
	std::string GetTarget(void) const;

private:
	// コンストラクタ
	Manager();
	// デストラクタ
	~Manager();

	// ルート生成
	template <typename T>
	void CreateRoot(const std::string& name, const std::initializer_list<T>& fileName, const bool& geoFlag = false);

	// パイプ生成
	void CreatePipe(const std::string& name, std::weak_ptr<Root>root, const std::initializer_list<unsigned char>& index,
		const D3D12_PRIMITIVE_TOPOLOGY_TYPE& type, const bool& depth = false);

	// 初期化
	void Init(void);


	// ライブラリターゲット
	std::string target;

	// ルート
	std::unordered_map<std::string, std::shared_ptr<Root>>root;

	// パイプ
	std::unordered_map<std::string, std::shared_ptr<Pipe>>pipe;

	// テクスチャ
	std::unordered_map<int, std::shared_ptr<Texture>>tex;

	// プリミティブ
	std::vector<std::shared_ptr<Primitive>>prim;

	// ライブラリ
	std::unordered_map<std::string, std::shared_ptr<MyLib>>lib;
};