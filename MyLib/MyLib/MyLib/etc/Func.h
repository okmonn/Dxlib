#pragma once
#include <string>

namespace func
{
	// �~�����擾
	inline constexpr float PI(void);

	// ���W�A���ϊ�
	float Rad(const float& angle);

	// �����R�[�h�ϊ�
	std::wstring ChangeCode(const std::string& code);
	std::string ChangeCode(const std::wstring& code);
}
