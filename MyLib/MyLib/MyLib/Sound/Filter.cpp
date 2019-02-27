#include "Filter.h"
#include "Sound.h"
#include "../etc/Func.h"
#include <algorithm>

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
void Filter::LowPass(const snd::FilterParam& param, const snd::Info& info)
{
	float omega = 2.0f * func::PI() * param.cutoff / info.sample;
	float alpha = std::sin(omega) / (2.0f * param.q);

	a[0] =  1.0f + alpha;
	a[1] = -2.0f * std::cos(omega);
	a[2] =  1.0f - alpha;

	b[0] = (1.0f - std::cos(omega)) / 2.0f;
	b[1] =  1.0f - std::cos(omega);
	b[2] = (1.0f - std::cos(omega)) / 2.0f;
}

// ハイパスフィルタ
void Filter::HighPass(const snd::FilterParam & param, const snd::Info & info)
{
	float omega = 2.0f * func::PI() * param.cutoff / info.sample;
	float alpha = std::sin(omega) / (2.0f * param.q);

	a[0] =  1.0f + alpha;
	a[1] = -2.0f * std::cos(omega);
	a[2] =  1.0f - alpha;

	b[0] =  (1.0f + std::cos(omega)) / 2.0f;
	b[1] = -(1.0f + std::cos(omega));
	b[2] =  (1.0f + std::cos(omega)) / 2.0f;
}

// バンドパス
void Filter::BandPass(const snd::FilterParam & param, const snd::Info & info)
{
	float omega = 2.0f * func::PI() * param.cutoff / info.sample;
	float alpha = std::sin(omega) * std::sinh(logf(2.0f) / 2.0f * param.q * omega / std::sin(omega));

	a[0] =  1.0f + alpha;
	a[1] = -2.0f * std::cos(omega);
	a[2] =  1.0f - alpha;

	b[0] =  alpha;
	b[1] =  0.0f;
	b[2] = -alpha;

}

// 実行
void Filter::Execution(std::vector<float>& input)
{
	for (auto& i : input)
	{
		this->input[1] = this->input[0];
		this->input[0] = i;

		i = b[0] / a[0] * this->input[0]
		  + b[1] / a[0] * this->input[0]
		  + b[2] / a[0] * this->input[1]
		  - a[1] / a[0] * out[0]
		  - a[2] / a[0] * out[1];

		out[1] = out[0];
		out[0] = i;
	}
}
