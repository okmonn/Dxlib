#include "MyLib/MyLib.h"

int main()
{
	const Vec2 winSize = { 640, 480 };
	std::shared_ptr<MyLib>lib;
	lib = std::make_shared<MyLib>(winSize);

	Texture tex("Š®¬.png");
	
	Sound sound;
	
	bool stop = false;
	while (lib->CheckMsg() && KEY.CheckKey(KeyCode::Escape) == false)
	{
		lib->Clear();
		lib->Draw(tex, 1.0f);
		lib->Execution();
		
		auto hr = lib->GetDropFilePass();
		if (hr.size() > 0)
		{
			sound.Load(hr);
			sound.Play(false);
		}

		if (KEY.Trigger(KeyCode::Space))
		{
			sound.Stop();
			continue;
			if (stop == false)
			{
				
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
			
		}
		else if (KEY.CheckKey(KeyCode::Left))
		{
			sound.pan -= 1.0f;
			
		}
		printf("%f\n", sound.pan);
	}

	return 0;
}