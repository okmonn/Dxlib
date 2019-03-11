#pragma once
#include <vector>
#include <memory>
#include <thread>

class MyLib;
class Texture;
class Sound;
class Mouse;
class ParamMane;
class Waves;
class DFT;

// �S������
class Mixer
{
public:
	// �R���X�g���N�^
	Mixer();
	// �f�X�g���N�^
	~Mixer();

	// ����
	void Run(void);

private:
	Mixer(const Mixer&) = delete;
	void operator=(const Mixer&) = delete;

	// ���Z�b�g
	void Reset(void);

	// ����
	void UpData(void);

	// �Đ��E��~
	void PlayAndStop(void);

	// �g�`�`��
	void DrawWaves(void);

	// �U��
	void DrawAmp(void);


	// ���C�u����
	std::shared_ptr<MyLib>lib;

	// �T�E���h
	std::shared_ptr<Sound>sound;

	// �}�E�X
	std::shared_ptr<Mouse>mouse;

	// �p�����[�^
	std::unique_ptr<ParamMane>param;

	// �E�F�[�u
	std::unique_ptr<Waves>wave;

	// �t�[���G�ϊ�
	std::unique_ptr<DFT>dft;

	// �Đ��t���O
	bool play;

	// �X���b�h�t���O
	bool threadFlag;

	// �X���b�h
	std::vector<std::thread>th;
};
