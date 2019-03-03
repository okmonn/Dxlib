#include "Thumb.h"
#include <MyLib.h>

// �R���X�g���N�^
Thumb::Thumb(const Vec2f& pos, const Vec2f& size, const float& min, const float& max, const float& now) :
	pos(pos), size(size), min(min), max(max), effect(now), angle(func::PI() + (func::PI() * (now / max)))
{
	tex = std::make_unique<Texture>("_rsc/thumb.png");
	tex->pos    = pos;
	tex->size   = size;
	tex->rotate = angle;
}

// �f�X�g���N�^
Thumb::~Thumb()
{
}

// ����
void Thumb::UpData(void)
{
	//�N���b�s���O
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

// ���݂̒l�擾
float Thumb::GetEffect(void) const
{
	return effect;
}
