#pragma once
#include <Math/Vector2.h>
#include <memory>

class MyLib;

// �}�E�X
class Mouse
{
public:
	// �R���X�g���N�^
	Mouse(std::weak_ptr<MyLib>lib);
	// �f�X�g���N�^
	~Mouse();

	// ����
	void UpData(void);

	// �N���b�N���W�擾
	Vec2f GetClick(void) const;

	// ���W�擾
	Vec2f GetPos(void) const;

private:
	// ���C�u����
	std::weak_ptr<MyLib>lib;

	// �N���b�N���W
	Vec2f click;

	// �ړ����W
	Vec2f pos;
};
