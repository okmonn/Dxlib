#include "Mouse.h"
#include <MyLib.h>

// �R���X�g���N�^
Mouse::Mouse(std::weak_ptr<MyLib> lib) : 
	lib(lib), click(-1.0f), pos(-1.0f)
{
}

// �f�X�g���N�^
Mouse::~Mouse()
{
}

// ����
void Mouse::UpData(void)
{
	if (KEY.CheckKey(KeyCode::LButton))
	{
		Vec2 tmp = lib.lock()->GetMousePos();
		if (click < 0.0f)
		{
			click = Vec2f(tmp.x, tmp.y);
		}
		pos = Vec2f(tmp.x, tmp.y);
	}
	else
	{
		click = -1.0f;
		pos   = click;
	}
}

// �N���b�N���W�擾
Vec2f Mouse::GetClick(void) const
{
	return click;
}

// ���W�擾
Vec2f Mouse::GetPos(void) const
{
	return pos;
}
