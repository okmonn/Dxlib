#include "Mixer/Mixer.h"

#ifdef _DEBUG
int main()
#else
#endif
{
	Mixer mix;
	mix.Run();

	return 0;
}