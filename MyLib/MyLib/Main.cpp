#include "MyLib/MyLib.h"

int main()
{
	const Vec2 winSize = { 640, 480 };
	std::shared_ptr<MyLib>lib;
	lib = std::make_shared<MyLib>(winSize);
	std::shared_ptr<MyLib>lib2;
	lib2 = std::make_shared<MyLib>(lib, winSize);

	Texture tex("Š®¬.png");
	
	Sound sound("‚¦‚ê‚­‚Æ‚è‚Á‚­‚¦‚ñ‚¶‚¥‚¤.wav");
	auto s = sound;
	s.delayParam.time = 0.5f;
	s.Play(false);
	
	bool stop = false;
	while (lib->CheckMsg() && KEY.CheckKey(KeyCode::Escape) == false)
	{
		lib->Clear();
		lib->Draw(tex, 1.0f);
		lib->Execution();

		if (KEY.Trigger(KeyCode::Space))
		{
			sound.Play(true);
		}
		if (KEY.CheckKey(KeyCode::Up))
		{
			sound.volume += 1.0f;
		}
		else if (KEY.CheckKey(KeyCode::Down))
		{
			sound.volume -= 1.0f;
			if (sound.volume < 0.0f)
			{
				sound.volume = 0.0f;
			}
		}
	}

	return 0;
}