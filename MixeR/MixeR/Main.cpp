#include "Mixer/Mixer.h"

#ifdef _DEBUG
int main()
#else
int __stdcall WinMain(void* hInstance, void* hPrevInstance, char* lpCmdLine, int nShowCmd)
#endif
{
	Mixer mix;
	mix.Run();

	return 0;
}