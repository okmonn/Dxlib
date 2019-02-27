#include "Delay.h"
#include "Sound.h"
#include <algorithm>

// �R���X�g���N�^
Delay::Delay(Sound* sound) : 
	sound(sound)
{
}

// �f�X�g���N�^
Delay::~Delay()
{
}

// ���s
void Delay::Execution(const uint& offset)
{
	////�f�[�^�ǉ�
	//std::copy(sound->wave.begin(), sound->wave.end(), std::back_inserter(old));

	////�x���Ԋu
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

	//�x���Ԋu
	float delay = sound->info.sample * sound->delayParam.time;

	for (uint ch = 0; ch < sound->info.channel; ++ch)
	{
		uint index = ch;
		std::vector<float>tmp(sound->wave.size() / sound->info.channel);
		std::for_each(tmp.begin(), tmp.end(), [&](float& i)->void {
			i = sound->wave[index];
			index += sound->info.channel;
		});

		//�f�[�^�ǉ�
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

// �ߋ��f�[�^�N���A
void Delay::Clear(void)
{
	old.clear();
}
