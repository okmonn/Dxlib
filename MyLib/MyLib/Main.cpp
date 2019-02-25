#include "MyLib/MyLib.h"

int main()
{
	const Vec2 winSize = { 640, 480 };
	MyLib lib(winSize);
	lib.Camera({ 0.0f, 0.0f, -1.0f }, {0.0f, 0.0f, 0.0f});

	Texture tex;
	tex.Load("äÆê¨.png");
	float angle = 0.0f;
	
	while (lib.CheckMsg())
	{
		tex.rotate.z = angle;
		lib.Clear();
		lib.Draw(tex);
		lib.Execution();
		angle += 0.01f;
	}

	return 0;
}