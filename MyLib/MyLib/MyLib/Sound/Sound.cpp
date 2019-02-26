#include "Sound.h"
#include "XAudio2.h"
#include "VoiceCallback.h"
#include "SndLoader.h"
#include <ks.h>
#include <ksmedia.h>

// �o�b�t�@��
#define BUFFER 2
// �I�t�Z�b�g
#define OFFSET 100;

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
	back    = std::unique_ptr<VoiceCallback>();
	sample  = 0;
	bit     = 0;
	channel = 0;

	wave.resize(BUFFER);
}

// �f�X�g���N�^
Sound::~Sound()
{
	threadFlag = false;
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
	desc.Format.nChannels       = channel;
	desc.Format.nSamplesPerSec  = sample;
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
		OutputDebugString(_T("\n�\�[�X�{�C�X�����F���s\n"));
	}

	return hr;
}

// �ǂݍ���
int Sound::Load(const std::string & fileName)
{
	if (SndLoader::Get().Load(fileName) != 0)
	{
		return -1;
	}

	this->fileName = fileName;
	sample  = SndLoader::Get().GetSample(fileName);
	bit     = SndLoader::Get().GetBit(fileName);
	channel = SndLoader::Get().GetChannel(fileName);

	CreateVoice();

	if (th.joinable() == false)
	{
		th = std::thread(&Sound::StreamFile, this);
	}

	return 0;
}

// �Đ�
long Sound::Play(const bool & loop)
{
	auto hr = voice->Start();
	if (FAILED(hr))
	{
		OutputDebugString(_T("\n�Đ��F���s\n"));
		return hr;
	}

	this->loop = loop;

	return hr;
}

// ��~
long Sound::Stop(void)
{
	auto hr = voice->Stop();
	if (FAILED(hr))
	{
		OutputDebugString(_T("\n��~�F���s\n"));
	}

	return hr;
}

// �t�@�C���ǂݍ��݃f�[�^�񓯊�
void Sound::StreamFile(void)
{
	const uint bps = sample * (bit / 8) * channel / OFFSET;
	XAUDIO2_BUFFER buf{};
	XAUDIO2_VOICE_STATE st{};
	while (threadFlag)
	{
		voice->GetState(&st);
		if (st.BuffersQueued > BUFFER)
		{
			continue;
		}

		//�c��T�C�Y�v�Z
		uint size = (SndLoader::Get().GetWave(fileName).size() - read > bps)
			? bps
			: uint((SndLoader::Get().GetWave(fileName).size())) - read - 1;

		std::vector<float>tmp(&SndLoader::Get().GetWave(fileName)[read], &SndLoader::Get().GetWave(fileName)[read + size]);
		wave[index] = tmp;

		buf.AudioBytes = uint(sizeof(float) * wave[index].size());
		buf.pAudioData = (uchar*)(wave[index].data());
		auto hr = voice->SubmitSourceBuffer(&buf);
		if (FAILED(hr))
		{
			OutputDebugString(_T("\n�T�E���h�f�[�^�ǉ��F���s\n"));
			continue;
		}

		index = (index + 1 >= BUFFER) ? 0 : ++index;
		read += size;
		if (read + 1 >= SndLoader::Get().GetWave(fileName).size())
		{
			if (loop == false)
			{
				Stop();
				index = 0;
			}
			read = 0;
		}
	}
}
