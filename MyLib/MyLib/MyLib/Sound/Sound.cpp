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

// �o�b�t�@��
#define BUFFER 2

// �X�s�[�J�[�ݒ�p�z��
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

// �R���X�g���N�^
Sound::Sound() :
	voice(nullptr), index(0), read(0), loop(false), threadFlag(true)
{
	back        = std::make_unique<VoiceCallback>();
	delay       = std::make_unique<Delay>(this);
	filter      = std::make_unique<Filter>(this);
	info        = {};
	distortion  = 1.0f;
	compressor  = { 1.0f, 1.0f / 10.0f };
	pan         = 0.0f;
	volume      = 1.0f;
	delayParam  = { 1.0f, 0.0f, 0 };
	filterParam = {};

	wave.resize(BUFFER);
}

// �R���X�g���N�^
Sound::Sound(const std::string& fileName) :
	voice(nullptr), index(0), read(0), loop(false), threadFlag(true)
{
	back        = std::make_unique<VoiceCallback>();
	delay       = std::make_unique<Delay>(this);
	filter      = std::make_unique<Filter>(this);
	info        = {};
	distortion  = 1.0f;
	compressor  = { 1.0f, 1.0f / 10.0f };
	pan         = 0.0f;
	volume      = 1.0f;
	delayParam  = { 1.0f, 0.0f, 0 };
	filterParam = {};

	wave.resize(BUFFER);

	Load(fileName);
}

// �R�s�[�R���X�g���N�^
Sound::Sound(const Sound& sound)
{
	back        = std::make_unique<VoiceCallback>();
	delay       = std::make_unique<Delay>(this);
	filter      = std::make_unique<Filter>(this);
	index       = 0;
	read        = 0;
	loop        = false;
	threadFlag  = true;
	info        = sound.info;
	distortion  = sound.distortion;
	compressor  = sound.compressor;
	pan         = sound.pan;
	volume      = sound.volume;
	delayParam  = sound.delayParam;
	filterParam = sound.filterParam;
	fileName    = sound.fileName;

	wave.resize(BUFFER);

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

// �f�X�g���N�^
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

// �\�[�X�{�C�X����
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
		func::DebugLog("�\�[�X�{�C�X�����F���s");
	}

	return hr;
}

// �ǂݍ���
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

// ���[�p�X�t�B���^
void Sound::LowPass(void)
{
	filter->LowPass(filterParam, info);
}

// �n�C�p�X�t�B���^
void Sound::HighPass(void)
{
	filter->HighPass(filterParam, info);
}

// �o���h�p�X
void Sound::BandPass(void)
{
	filter->BandPass(filterParam, info);
}

// �Đ�
long Sound::Play(const bool& loop)
{
	auto hr = voice->Start();
	if (FAILED(hr))
	{
		func::DebugLog("�Đ��F���s");
		return hr;
	}

	this->loop = loop;

	return hr;
}

// ��~
long Sound::Stop(void) const
{
	//�o�b�t�@�����I���܂őҋ@
	WaitForSingleObject(back->handle[1], INFINITE);

	auto hr = voice->Stop();
	if (FAILED(hr))
	{
		func::DebugLog("��~�F���s");
	}

	return hr;
}

// �t�@�C���ǂݍ��݃f�[�^�񓯊�
void Sound::StreamFile(void)
{
	const uint bps = (info.sample * info.channel) / Offset();
	XAUDIO2_BUFFER buf{};
	XAUDIO2_VOICE_STATE st{};
	while (threadFlag)
	{
		voice->GetState(&st);
		if (st.BuffersQueued >= BUFFER)
		{
			continue;
		}

		//�c��T�C�Y�v�Z
		uint size = (SndLoader::Get().GetWave(fileName)->size() - read > bps)
			? bps
			: uint((SndLoader::Get().GetWave(fileName)->size())) - read - 1;

		wave[index].assign(&SndLoader::Get().GetWave(fileName)->at(read), &SndLoader::Get().GetWave(fileName)->at(read + size));
		if (wave[index].size() % info.channel)
		{
			wave[index].resize(wave[index].size() + wave[index].size() % info.channel);
		}

		effe->Execution(wave[index]);
		delay->Execution(wave[index], read);
		filter->Execution(wave[index]);

		buf.AudioBytes = uint(sizeof(float) * wave[index].size());
		buf.pAudioData = (uchar*)(wave[index].data());
		auto hr = voice->SubmitSourceBuffer(&buf);
		if (FAILED(hr))
		{
			func::DebugLog("�T�E���h�f�[�^�ǉ��F���s");
			continue;
		}

		index = (index + 1 >= 2) ? 0 : ++index;
		read += size;

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

// 1�񏈗�����f�[�^�p�I�t�Z�b�g
inline constexpr uint Sound::Offset(void) const
{
	return 100;
}

// ���݂̔g�`�f�[�^�擾
inline std::vector<float> Sound::GetWave(void) const
{
	return wave[index];
}

// ���Z�q�I�[�o�[���[�h
void Sound::operator=(const Sound & sound)
{
	back.reset(new VoiceCallback()); 
	delay.reset(new Delay(this));
	filter.reset(new Filter(this));
	index       = 0;
	read        = 0;
	loop        = false;
	threadFlag  = true;
	info        = sound.info;
	distortion  = sound.distortion;
	compressor  = sound.compressor;
	pan         = sound.pan;
	volume      = sound.volume;
	delayParam  = sound.delayParam;
	filterParam = sound.filterParam;
	fileName    = sound.fileName;

	wave.resize(BUFFER);

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
