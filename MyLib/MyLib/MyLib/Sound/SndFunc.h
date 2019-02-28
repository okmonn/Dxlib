#pragma once
#include "../etc/Define.h"
#include <string>
#include <vector>

namespace snd
{
	// RIFF
	struct RIFF {
		//ID
		unsigned char id[4];
		//�T�C�Y
		long size;
		//�^�C�v
		unsigned char type[4];
	};

	// FMT
	struct FMT {
		//ID
		unsigned char id[4];
		//�T�C�Y
		long size;
		//�^�C�v
		short type;
		//�`�����l��
		short channel;
		//�T���v�����O���g��
		long sample;
		//�o�C�g
		long byte;
		//�u���b�N�T�C�Y
		short block;
		//�ʎq���r�b�g��
		short bit;
	};

	// DATA
	struct DATA {
		//ID
		std::string id;
		//�T�C�Y
		long size;
	};

	// �T�E���h���
	struct Info {
		//�T���v�����O���g��
		uint sample;
		//�ʎq���r�b�g��
		uint bit;
		//�`�����l����
		uint channel;
	};
	
	// �R���v���b�T�p�����[�^
	struct Compressor {
		//臒l
		float threshold;
		//���V�I
		float ratio;
	};

	// �f�B���C�p�����[�^
	struct Delay {
		//������
		float decay;
		//�x������
		float time;
		//���[�v��
		uint loop;
	};

	// �t�B���^�p�����[�^
	struct FilterParam {
		//�J�b�g�I�t���g��
		float cutoff;
		//�N�I���e�B�t�@�N�^�E�ш敝
		float bw;
	};


	// RIFF�̓ǂݍ���
	int LoadRIFF(RIFF& riff, FILE* file);

	// FMT�̓ǂݍ���
	int LoadFMT(FMT& fmt, FILE* file);

	// DATA�̓ǂݍ���
	int LoadDATA(DATA& data, FILE* file);

	// 8�r�b�g�g�`�̓ǂݍ���
	int LoadWave8(std::vector<float>& data, FILE* file);

	// 16�r�b�g�g�`�̓ǂݍ���
	int LoadWave16(std::vector<float>& data, FILE* file);
}
