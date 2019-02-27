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
void Delay::Execution(const uint& offset)
{
	////データ追加
	//std::copy(sound->wave.begin(), sound->wave.end(), std::back_inserter(old));

	////遅延間隔
	//float delay = sound->info.sample * sound->delayParam.time;

	//for (unsigned int i = 0; i < sound->wave.size(); ++i)
	//{
	//	for (unsigned int loop = 1; loop <= sound->delayParam.loop; ++loop)
	//	{
	//		int m = offset + i - uint(delay * loop);
	//		if (m >= 0)
	//		{
	//			sound->wave[i] += old[m] * std::pow(sound->delayParam.decay, float(loop));
	//		}
	//	}
	//}


	old.resize(sound->info.channel);

	//遅延間隔
	float delay = sound->info.sample * sound->delayParam.time;

	for (uint ch = 0; ch < sound->info.channel; ++ch)
	{
		uint index = ch;
		std::vector<float>tmp(sound->wave.size() / sound->info.channel);
		std::for_each(tmp.begin(), tmp.end(), [&](float& i)->void {
			i = sound->wave[index];
			index += sound->info.channel;
		});

		//データ追加
		std::copy(tmp.begin(), tmp.end(), std::back_inserter(old[ch]));

		index = 0;
		for (uint i = ch; i < sound->wave.size(); i += sound->info.channel)
		{
			for (uint loop = 1; loop <= sound->delayParam.loop; ++loop)
			{
				int m = (offset / sound->info.channel) + index - uint(delay * loop);
				if (m >= 0)
				{
					sound->wave[i] += old[ch][m] * std::pow(sound->delayParam.decay, float(loop));
				}
			}
			++index;
		}
	}
}

// 過去データクリア
void Delay::Clear(void)
{
	old.clear();
}
