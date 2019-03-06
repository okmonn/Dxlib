#include "Filter.h"
#include "Sound.h"
#include "../etc/Func.h"
#include <algorithm>
#include <minmax.h>

// コンストラクタ
Filter::Filter(Sound* sound) : 
	sound(sound)
{
	memset(&input[0], 0, sizeof(input));
	memset(&out[0],   0, sizeof(out));
	memset(&a[0],     0, sizeof(a));
	memset(&b[0],     0, sizeof(b));
	a[0] = 1.0f;
	b[0] = 1.0f;
}

// デストラクタ
Filter::~Filter()
{
}

// ローパスフィルタ
void Filter::LowPass(void)
{
	float omega = 2.0f * func::PI() * sound->filterParam.cutoff / sound->info.sample;
	float alpha = std::sin(omega) / (2.0f * sound->filterParam.bw);

	a[0] =  1.0f + alpha;
	a[1] = -2.0f * std::cos(omega);
	a[2] =  1.0f - alpha;

	b[0] = (1.0f - std::cos(omega)) / 2.0f;
	b[1] =  1.0f - std::cos(omega);
	b[2] = (1.0f - std::cos(omega)) / 2.0f;
}

// ハイパスフィルタ
void Filter::HighPass(void)
{
	float omega = 2.0f * func::PI() * sound->filterParam.cutoff / sound->info.sample;
	float alpha = std::sin(omega) / (2.0f * sound->filterParam.bw);

	a[0] =  1.0f + alpha;
	a[1] = -2.0f * std::cos(omega);
	a[2] =  1.0f - alpha;

	b[0] =  (1.0f + std::cos(omega)) / 2.0f;
	b[1] = -(1.0f + std::cos(omega));
	b[2] =  (1.0f + std::cos(omega)) / 2.0f;
}

// バンドパスフィルタ
void Filter::BandPass(void)
{
	float omega = 2.0f * func::PI() * sound->filterParam.cutoff / sound->info.sample;
	float alpha = std::sin(omega) * std::sinh(logf(2.0f) / 2.0f * sound->filterParam.bw * omega / std::sin(omega));

	a[0] =  1.0f + alpha;
	a[1] = -2.0f * std::cos(omega);
	a[2] =  1.0f - alpha;

	b[0] =  alpha;
	b[1] =  0.0f;
	b[2] = -alpha;

}

// ノッチフィルタ
void Filter::Notch(void)
{
	float omega = 2.0f * func::PI() * sound->filterParam.cutoff / sound->info.sample;
	float alpha = std::sin(omega) * std::sinh(std::log(2.0f) / 2.0f * sound->filterParam.bw * omega / std::sin(omega));

	a[0] =  1.0f + alpha;
	a[1] = -2.0f * std::cos(omega);
	a[2] =  1.0f - alpha;

	b[0] =  1.0f;
	b[1] = -2.0f * std::cos(omega);
	b[2] =  1.0f;
}

// オールパスフィルタ
void Filter::AllPass(void)
{
	float omega = 2.0f * func::PI() * sound->filterParam.cutoff / sound->info.sample;
	float alpha = std::sin(omega) / (2.0f * sound->filterParam.bw);

	a[0] =  1.0f + alpha;
	a[1] = -2.0f * std::cos(omega);
	a[2] =  1.0f - alpha;
	
	b[0] =  1.0f - alpha;
	b[1] = -2.0f * std::cos(omega);
	b[2] =  1.0f + alpha;
}

// 実行
void Filter::Execution(std::vector<float>& input)
{
	sound->filterParam.cutoff = max(sound->filterParam.cutoff, 10.0f);
	sound->filterParam.cutoff = min(sound->filterParam.cutoff, func::Floor(float(sound->info.sample / 2), 3));
	sound->filterParam.bw = max(sound->filterParam.bw, 0.01f);

	for (auto& i : input)
	{
		//変換前保持
		float tmp = i;

		i = b[0] / a[0] * tmp
		  + b[1] / a[0] * this->input[0]
		  + b[2] / a[0] * this->input[1]
		  - a[1] / a[0] * out[0]
		  - a[2] / a[0] * out[1];

		this->input[1] = this->input[0];
		this->input[0] = tmp;

		out[1] = out[0];
		out[0] = i;
	}
}
