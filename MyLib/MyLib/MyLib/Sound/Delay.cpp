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
void Delay::Execution(std::vector<float>& input, const uint& offset)
{
	//�f�[�^�ǉ�
	std::copy(input.begin(), input.end(), std::back_inserter(old));

	if (sound->delayParam.loop == 0)
	{
		return;
	}

	//�x���Ԋu
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

// �ߋ��f�[�^�N���A
void Delay::Clear(void)
{
	old.clear();
}
