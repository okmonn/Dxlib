#include "Sound.h"
#include "XAudio2.h"
#include "VoiceCallback.h"
#include "SndLoader.h"
#include "Effector.h"
#include "Delay.h"
#include "Filter.h"
#include "../etc/Func.h"
#include <ks.h>
#include <ksmedia.h>

// スピーカー設定用配列
const ulong spk[] = {
	KSAUDIO_SPEAKER_MONO,
	KSAUDIO_SPEAKER_STEREO,
	KSAUDIO_SPEAKER_STEREO | SPEAKER_LOW_FREQUENCY,
	KSAUDIO_SPEAKER_QUAD,
	0,
	KSAUDIO_SPEAKER_5POINT1,
	0,
	KSAUDIO_SPEAKER_7POINT1_SURROUND
};

// コンストラクタ
Sound::Sound() :
	voice(nullptr), read(0), loop(false), threadFlag(true)
{
	back        = std::make_unique<VoiceCallback>();
	delay       = std::make_unique<Delay>(this);
	filter      = std::make_unique<Filter>(this);
	info        = {};
	distortion  = 1.0f;
	compressor  = { 1.0f, 1.0f / 10.0f };
	volume      = 1.0f;
	delayParam  = { 1.0f, 0.0f, 1 };
	filterParam = {};
}

// コンストラクタ
Sound::Sound(const std::string& fileName) :
	voice(nullptr), read(0), loop(false), threadFlag(true)
{
	back        = std::make_unique<VoiceCallback>();
	delay       = std::make_unique<Delay>(this);
	filter      = std::make_unique<Filter>(this);
	info        = {};
	distortion  = 1.0f;
	compressor  = { 1.0f, 1.0f / 10.0f };
	volume      = 1.0f;
	delayParam  = { 1.0f, 0.0f, 1 };
	filterParam = {};

	Load(fileName);
}

// コピーコンストラクタ
Sound::Sound(const Sound& sound)
{
	back        = std::make_unique<VoiceCallback>();
	delay       = std::make_unique<Delay>(this);
	filter      = std::make_unique<Filter>(this);
	read        = 0;
	loop        = false;
	threadFlag  = true;
	info        = sound.info;
	distortion  = sound.distortion;
	compressor  = sound.compressor;
	volume      = sound.volume;
	delayParam  = sound.delayParam;
	filterParam = sound.filterParam;
	fileName    = sound.fileName;

	CreateVoice();

	effe = std::make_unique<Effector>(this);
	if (fileName.size() > 0)
	{
		if (th.joinable() == false)
		{
			th = std::thread(&Sound::StreamFile, this);
		}
	}
}

// デストラクタ
Sound::~Sound()
{
	threadFlag = false;
	back->End();
	if (th.joinable() == true)
	{
		th.join();
	}
	Destroy(voice);
}

// ソースボイス生成
long Sound::CreateVoice(void)
{
	WAVEFORMATEXTENSIBLE desc{};
	desc.Format.cbSize          = sizeof(WAVEFORMATEXTENSIBLE) - sizeof(WAVEFORMATEX);
	desc.Format.nChannels       = info.channel;
	desc.Format.nSamplesPerSec  = info.sample;
	desc.Format.nBlockAlign     = sizeof(float) * desc.Format.nChannels;
	desc.Format.wBitsPerSample  = sizeof(float) * 8;
	desc.Format.nAvgBytesPerSec = desc.Format.nSamplesPerSec * desc.Format.nBlockAlign;
	desc.Format.wFormatTag      = WAVE_FORMAT_EXTENSIBLE;

	desc.dwChannelMask               = spk[desc.Format.nChannels - 1];
	desc.Samples.wValidBitsPerSample = desc.Format.wBitsPerSample;
	desc.SubFormat                   = KSDATAFORMAT_SUBTYPE_IEEE_FLOAT;

	auto hr = XAudio2::Get().GetAudio()->CreateSourceVoice(&voice, (WAVEFORMATEX*)(&desc), 0, 1.0f, &(*back));
	if (FAILED(hr))
	{
		func::DebugLog("ソースボイス生成：失敗");
	}

	return hr;
}

// 読み込み
int Sound::Load(const std::string& fileName)
{
	if (SndLoader::Get().Load(fileName) != 0)
	{
		return -1;
	}

	this->fileName = fileName;
	info = SndLoader::Get().GetInfo(fileName);
	filterParam = { func::Floor(float(info.sample / 2), 3), 1.0f / std::sqrt(2.0f) };

	CreateVoice();

	effe = std::make_unique<Effector>(this);
	if (th.joinable() == false)
	{
		th = std::thread(&Sound::StreamFile, this);
	}

	return 0;
}

// ローパスフィルタ
void Sound::LowPass(void)
{
	const float max = func::Floor(float(info.sample / 2), 3);
	const float min = 17.0f;
	if (filterParam.cutoff > max)
	{
		filterParam.cutoff = max;
	}
	else if (filterParam.cutoff < min)
	{
		filterParam.cutoff = min;
	}
	filter->LowPass(filterParam, info);
}

// ハイパスフィルタ
void Sound::HighPass(void)
{
	const float max = func::Floor(float(info.sample / 2), 3);
	const float min = 17.0f;
	if (filterParam.cutoff > max)
	{
		filterParam.cutoff = max;
	}
	else if (filterParam.cutoff < min)
	{
		filterParam.cutoff = min;
	}
	filter->HighPass(filterParam, info);
}

// バンドパス
void Sound::BandPass(void)
{
	const float max = func::Floor(float(info.sample / 2), 3);
	const float min = 17.0f;
	if (filterParam.cutoff > max)
	{
		filterParam.cutoff = max;
	}
	else if (filterParam.cutoff < min)
	{
		filterParam.cutoff = min;
	}
	filter->BandPass(filterParam, info);
}

// 再生
long Sound::Play(const bool& loop)
{
	auto hr = voice->Start();
	if (FAILED(hr))
	{
		func::DebugLog("再生：失敗");
		return hr;
	}

	this->loop = loop;

	return hr;
}

// 停止
long Sound::Stop(void) const
{
	//バッファ処理終了まで待機
	WaitForSingleObject(back->handle[1], INFINITE);

	auto hr = voice->Stop();
	if (FAILED(hr))
	{
		func::DebugLog("停止：失敗");
	}

	return hr;
}

// ファイル読み込みデータ非同期
void Sound::StreamFile(void)
{
	const uint bps = (info.sample * info.channel) / Offset();
	XAUDIO2_BUFFER buf{};
	while (threadFlag)
	{
		//残りサイズ計算
		uint size = (SndLoader::Get().GetWave(fileName)->size() - read > bps)
			? bps
			: uint((SndLoader::Get().GetWave(fileName)->size())) - read - 1;

		wave.assign(&SndLoader::Get().GetWave(fileName)->at(read), &SndLoader::Get().GetWave(fileName)->at(read + size));
		if (wave.size() % info.channel)
		{
			wave.resize(wave.size() + wave.size() % info.channel);
		}
		effe->Execution();
		delay->Execution(read);
		filter->Execution();

		buf.AudioBytes = uint(sizeof(float) * wave.size());
		buf.pAudioData = (uchar*)(wave.data());
		auto hr = voice->SubmitSourceBuffer(&buf);
		if (FAILED(hr))
		{
			func::DebugLog("サウンドデータ追加：失敗");
			continue;
		}
		read += size;

		//バッファ処理開始まで待機
		WaitForSingleObject(back->handle[0], INFINITE);
		if (read + 1 >= SndLoader::Get().GetWave(fileName)->size())
		{
			if (loop == false)
			{
				Stop();
			}
			read = 0;
			delay->Clear();
		}
	}
}

// 1回処理するデータ用オフセット
inline constexpr uint Sound::Offset(void) const
{
	return 100;
}

// 演算子オーバーロード
void Sound::operator=(const Sound & sound)
{
	back.reset(new VoiceCallback()); 
	delay.reset(new Delay(this));
	filter.reset(new Filter(this));
	read        = 0;
	loop        = false;
	threadFlag  = true;
	info        = sound.info;
	distortion  = sound.distortion;
	compressor  = sound.compressor;
	volume      = sound.volume;
	delayParam  = sound.delayParam;
	filterParam = sound.filterParam;
	fileName    = sound.fileName;

	CreateVoice();

	effe.reset(new Effector(this));
	if (fileName.size() > 0)
	{
		if (th.joinable() == false)
		{
			th = std::thread(&Sound::StreamFile, this);
		}
	}
}
