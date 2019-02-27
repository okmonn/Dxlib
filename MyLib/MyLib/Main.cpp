#include "MyLib/MyLib.h"

int main()
{
	const Vec2 winSize = { 640, 480 };
	std::shared_ptr<MyLib>lib;
	lib = std::make_shared<MyLib>(winSize);
	std::shared_ptr<MyLib>lib2;
	lib2 = std::make_shared<MyLib>(lib, winSize);

	Texture tex("Š®¬.png");
	
	Sound sound("mtgx.wav");
	sound.Play(true);
	
	bool stop = false;
	while (lib->CheckMsg() && KEY.CheckKey(KeyCode::Escape) == false)
	{
		lib->Clear();
		lib->Draw(tex, 1.0f);
		lib->Execution();

		if (KEY.Trigger(KeyCode::Space))
		{
			if (stop == false)
			{
				sound.Stop();
				stop = true;
			}
			else
			{
				sound.Play(true);
				stop = false;
			}
		}

		if (KEY.CheckKey(KeyCode::Right))
		{
			sound.pan += 1.0f;
			if (sound.pan >= 360.0f)
			{
				sound.pan = 0.0f;
			}
		}
		else if (KEY.CheckKey(KeyCode::Left))
		{
			sound.pan -= 1.0f;
			if (sound.pan < 0.0f)
			{
				sound.pan = 0.0f;
			}
		}
	}

	return 0;
}