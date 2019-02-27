#pragma once
#include "../Math/Vector3.h"
#include <string>
#include <vector>

namespace func
{
	// �f�o�b�O���O�o��
	void DebugLog(const std::string& log);

	// �~�����擾
	inline constexpr float PI(void);

	// ���W�A���ϊ�
	inline constexpr float Rad(const float& angle);

	// ���C���f�B�X�v���C�𑜓x�擾
	inline Vec2 GetDisplayResolution(void);

	// �����R�[�h�ϊ�
	std::wstring ChangeCode(const std::string& code);
	std::string ChangeCode(const std::wstring& code);

	// �����񌟍�
	bool FindChara(const char* input, const std::string& find);
	bool FindChara(const unsigned char* input, const std::string& find);

	// �C�ӂ̌�����؂�グ
	float Ceil(const float& i, const int& num);

	// �C�ӂ̌�����؂�̂�
	float Floor(const float& i, const int& num);

	// �C�ӂ̌�����l�̌ܓ�
	float Round(const float& i, const int& num);

	// �n�j���O��
	inline constexpr float Haninng(const unsigned int& index, const size_t& num);

	// ���U�t�[���G�ϊ�
	void DFT(const std::vector<float>& input, std::vector<float>& real, std::vector<float>& imag);

	// �t���U�t�[���G�ϊ�
	std::vector<float> IDFT(const std::vector<float>& real, const std::vector<float>& imag);

	// �����t�[���G�ϊ�
	void FFT(const std::vector<float>& input, std::vector<float>& real, std::vector<float>& imag);

	// �t�����t�[���G�ϊ�
	std::vector<float> IFFT(const std::vector<float>& real, const std::vector<float>& imag, const unsigned int& outNum);

	// �U���擾
	inline float Amplitude(const float& real, const float& imag);

	// �ʑ��擾
	inline float Phase(const float& real, const float& imag);
}
