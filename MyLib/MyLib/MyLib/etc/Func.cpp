#include "Func.h"
#include <Windows.h>

// �~�����擾
constexpr float func::PI(void)
{
	return 3.14159265358979323846f;
}

// ���W�A���ϊ�
float func::Rad(const float & angle)
{
	return angle * PI() / 180.0f;
}

// �����R�[�h�ϊ�
std::wstring func::ChangeCode(const std::string & code)
{
	//�T�C�Y�̎擾
	auto byteSize = MultiByteToWideChar(CP_ACP, MB_PRECOMPOSED | MB_ERR_INVALID_CHARS, code.c_str(), -1, nullptr, 0);

	std::wstring wstr;
	wstr.resize(byteSize);

	//�ϊ�
	byteSize = MultiByteToWideChar(CP_ACP, MB_PRECOMPOSED | MB_ERR_INVALID_CHARS, code.c_str(), -1, &wstr[0], byteSize);

	return wstr;
}

// �����R�[�h�ϊ�
std::string func::ChangeCode(const std::wstring & code)
{
	//�T�C�Y�̎擾
	auto byteSize = WideCharToMultiByte(CP_ACP, 0, code.c_str(), -1, nullptr, 0, nullptr, nullptr);

	std::string str;
	str.resize(byteSize);

	//�ϊ�
	byteSize = WideCharToMultiByte(CP_ACP, 0, code.c_str(), static_cast<int>(code.size()), &str[0], byteSize, nullptr, nullptr);

	return str;
}
