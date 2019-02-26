#include "MyLib/MyLib.h"
#include <minmax.h>

int main()
{
	const Vec2 winSize = { 640, 480 };
	MyLib lib(winSize);

	Texture tex;
	tex.Load("äÆê¨.png");

	Primitive prim(PrimitiveType::box);
	prim.pos[0] = 0.0f;
	prim.pos[1] = Vec2f(640.0f, 0.0f);
	prim.pos[2] = Vec2f(0.0f, 480.0f);
	prim.pos[3] = Vec2f(640.0f, 480.0f);
	
	while (lib.CheckMsg())
	{
		lib.Clear();
		lib.Draw(prim, 1.0f);
		lib.Execution();
	}

	return 0;
}