#include "Delay.h"
#include "Sound.h"
#include <algorithm>
#include <minmax.h>

// コンストラクタ
Delay::Delay(Sound* sound) : 
	sound(sound), time(0.0f), index(1), fade(1)
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

	//修正
	sound->delayParam.decay = max(sound->delayParam.decay, 0.01f);
	sound->delayParam.decay = min(sound->delayParam.decay, 1.0f);
	sound->delayParam.loop  = max(sound->delayParam.loop, 1);

	if (sound->delayParam.time <= 0.0f)
	{
		sound->delayParam.time = 0.0f;
		return;
	}

	if (time != sound->delayParam.time)
	{
		index = 0;
		fade  = uint(input.size() / sound->info.channel * sound->Offset());
	}

	//遅延間隔
	float delay = sound->info.sample * sound->delayParam.time;

	for (uint i = 0; i < input.size(); i += sound->info.channel)
	{
		for (uint ch = 0; ch < sound->info.channel; ++ch)
		{
			for (uint loop = 1; loop <= sound->delayParam.loop; ++loop)
			{
				int m = offset + i + ch - uint(delay * loop);
				if (m >= 0)
				{
					input[i + ch] += old[m] * std::pow(sound->delayParam.decay, float(loop)) * index / fade;
				}
			}
		}

		index = (index + 1) >= fade ? index : ++index;
	}

	if (index >= fade)
	{
		index = 1;
		fade  = 1;
	}

	time = sound->delayParam.time;
}

// 過去データクリア
void Delay::Clear(void)
{
	old.clear();
}
