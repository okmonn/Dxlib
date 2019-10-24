#pragma once
#include "etc/Vector2.h"
#include "Input/KeyCode.h"
#include "Func/Func.h"
#include <string>

namespace okmonn
{
	// 初期化
	bool Init(const Vec2& winSize, const Vec2& winPos = 0x80000000, const std::string& parent = "");

	// メッセージ確認
	bool CheckMsg(void);

	// キー入力
	bool CheckKey(const KeyCode& key);

	// トリガー入力
	bool Trigger(const KeyCode& key);

	// 画像読み込み
	int LoadImg(const std::string& fileName);

	// 画面クリア
	void Clear(void);

	// 本来の画像サイズで描画
	void DrawImg(const int& id, const Vec2& pos, const float& angle = 0.0f, const bool& turnX = false, const bool& turnY = false, const float& alpha = 1.0f);

	// 指定した画像サイズで描画
	void DrawImgRect(const int& id, const Vec2& pos, const Vec2& size, const float& angle = 0.0f,
		const bool& turnX = false, const bool& turnY = false, const float& alpha = 1.0f);

	// 指定した画像サイズで指定した矩形に分割して描画
	void DrawImgDivide(const int& id, const Vec2& pos, const Vec2& size, const Vec2& uvPos, const Vec2& uvSize, 
		const float& angle = 0.0f, const bool& turnX = false, const bool& turnY = false, const float& alpha = 1.0f);

	// ポイント描画
	void DrawPoint(const Vec2& pos, const float& r, const float& g, const float& b, const float& a = 1.0f);

	// ライン描画
	void DrawLine(const Vec2& pos1, const Vec2& pos2, const float& r, const float& g, const float& b, const float& a = 1.0f);

	// トライアングル描画
	void DrawTriangle(const Vec2& pos1, const Vec2& pos2, const Vec2& pos3, const float& r, const float& g, const float& b, const float& a = 1.0f);

	// ボックス描画
	void DrawBox(const Vec2& pos, const Vec2& size, const float& r, const float& g, const float& b, const float& a = 1.0f);
	
	// 実行
	void Execution(void);

	// ターゲットにするライブラリを変える（新しく作る際のライブラリ個別名を設定する）
	void ChangeTargetName(const std::string& name);

	// 現在ターゲットにしているライブラリ個別名を取得
	std::string GetNowTargetLibName(void);

	// テクスチャハンドル削除
	void DeleteImg(const int& id);

	// プリミティブデータ削除
	// 毎フレーム呼び出し推奨
	void DeletePrim(const bool& memReset = false);

	// 画像データ削除
	void DeleteImg(const std::string& fileName);
}
