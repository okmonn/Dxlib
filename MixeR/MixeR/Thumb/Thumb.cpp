#include "Thumb.h"
#include <MyLib.h>

// コンストラクタ
Thumb::Thumb(const Vec2f& pos, const Vec2f& size, const float& min, const float& max, const float& now) :
	pos(pos), size(size), min(min), max(max), effect(now), angle(func::PI() + (func::PI() * (now / max)))
{
	tex = std::make_unique<Texture>("_rsc/thumb.png");
	tex->pos    = pos;
	tex->size   = size;
	tex->rotate = angle;
}

// デストラクタ
Thumb::~Thumb()
{
}

// 処理
void Thumb::UpData(void)
{
	//クリッピング
	if (effect > max)
	{
		effect = max;
	}
	else if (effect < min)
	{
		effect = min;
	}

	angle = func::PI() + (func::PI() * (effect / max));
	tex->rotate = angle;
}

// 現在の値取得
float Thumb::GetEffect(void) const
{
	return effect;
}
