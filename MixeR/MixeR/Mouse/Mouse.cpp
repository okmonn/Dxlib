#include "Mouse.h"
#include <MyLib.h>

// コンストラクタ
Mouse::Mouse(std::weak_ptr<MyLib> lib) : 
	lib(lib), click(-1.0f), pos(-1.0f)
{
}

// デストラクタ
Mouse::~Mouse()
{
}

// 処理
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

// クリック座標取得
Vec2f Mouse::GetClick(void) const
{
	return click;
}

// 座標取得
Vec2f Mouse::GetPos(void) const
{
	return pos;
}
