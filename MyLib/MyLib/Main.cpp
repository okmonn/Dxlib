#include "MyLib/MyLib.h"

int main()
{
	const Vec2 winSize = { 640, 480 };
	MyLib lib(winSize);
	while (lib.CheckMsg())
	{
		lib.Clear();
		lib.Execution();
	}

	return 0;
}