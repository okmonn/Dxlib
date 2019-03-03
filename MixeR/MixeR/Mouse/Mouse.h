#pragma once
#include <Math/Vector2.h>
#include <memory>

class MyLib;

// マウス
class Mouse
{
public:
	// コンストラクタ
	Mouse(std::weak_ptr<MyLib>lib);
	// デストラクタ
	~Mouse();

	// 処理
	void UpData(void);

	// クリック座標取得
	Vec2f GetClick(void) const;

	// 座標取得
	Vec2f GetPos(void) const;

private:
	// ライブラリ
	std::weak_ptr<MyLib>lib;

	// クリック座標
	Vec2f click;

	// 移動座標
	Vec2f pos;
};
