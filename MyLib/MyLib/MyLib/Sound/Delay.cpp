#include "Delay.h"
#include "Sound.h"
#include <algorithm>

// コンストラクタ
Delay::Delay(Sound* sound) : 
	sound(sound)
{
}

// デストラクタ
Delay::~Delay()
{
}

// 実行
void Delay::Execution(std::vector<float>& input, const uint& offset)
{
	//データ追加
	std::copy(input.begin(), input.end(), std::back_inserter(old));

	if (sound->delayParam.loop == 0)
	{
		return;
	}

	//遅延間隔
	float delay = sound->info.sample * sound->delayParam.time;

	uint index = 0;
	for (auto& i : input)
	{
		for (uint loop = 1; loop <= sound->delayParam.loop; ++loop)
		{
			int m = offset + index - uint(delay * loop);
			if (m >= 0)
			{
				i += old[m] * std::pow(sound->delayParam.decay, float(loop));
			}
		}
		++index;
	}
}

// 過去データクリア
void Delay::Clear(void)
{
	old.clear();
}
