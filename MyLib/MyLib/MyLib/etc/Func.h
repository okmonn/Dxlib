#pragma once
#include <string>

namespace func
{
	// �f�o�b�O���O�o��
	void DebugLog(const std::string& log);

	// �~�����擾
	inline constexpr float PI(void);

	// ���W�A���ϊ�
	float Rad(const float& angle);

	// �����R�[�h�ϊ�
	std::wstring ChangeCode(const std::string& code);
	std::string ChangeCode(const std::wstring& code);

	// �����񌟍�
	bool FindChara(const char* input, const std::string& find);
	bool FindChara(const unsigned char* input, const std::string& find);
}
