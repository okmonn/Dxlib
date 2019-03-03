#pragma once
#include <Math/Vector2.h>
#include <memory>

class Texture;
class ParamMane;

// �܂�
class Thumb
{
	friend ParamMane;
public:
	// �R���X�g���N�^
	Thumb(const Vec2f& pos, const Vec2f& size, const float& min = 0.0f, const float& max = 1.0f, const float& now = 0.0f);
	// �f�X�g���N�^
	~Thumb();

	// ����
	void UpData(void);

	// ���݂̒l�擾
	float GetEffect(void) const;

private:
	// �e�N�X�`��
	std::unique_ptr<Texture>tex;

	// ���W
	Vec2f pos;

	// �T�C�Y
	Vec2f size;

	// �ŏ��l
	float min;

	// �ő�l
	float max;

	// ���݂̒l
	float effect;

	// ��]�p�x
	float angle;
};
