#include "MyLib/MyLib.h"

int main()
{
	const Vec2 winSize = { 640, 480 };
	MyLib lib(winSize);

	Texture tex("äÆê¨.png");
	
	while (lib.CheckMsg() && KEY.CheckKey(KeyCode::Escape) == false)
	{
		lib.Clear();
		lib.Draw(tex, 1.0f);
		lib.Execution();

		if (KEY.Trigger(KeyCode::Down))
		{
			tex.pos.y += 100.0f;
		}
	}

	return 0;
}