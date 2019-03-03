#pragma once
#include <Math/Vector2.h>
#include <memory>

class Texture;
class ParamMane;

// つまみ
class Thumb
{
	friend ParamMane;
public:
	// コンストラクタ
	Thumb(const Vec2f& pos, const Vec2f& size, const float& min = 0.0f, const float& max = 1.0f, const float& now = 0.0f);
	// デストラクタ
	~Thumb();

	// 処理
	void UpData(void);

	// 現在の値取得
	float GetEffect(void) const;

private:
	// テクスチャ
	std::unique_ptr<Texture>tex;

	// 座標
	Vec2f pos;

	// サイズ
	Vec2f size;

	// 最小値
	float min;

	// 最大値
	float max;

	// 現在の値
	float effect;

	// 回転角度
	float angle;
};
