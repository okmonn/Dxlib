#include "MyLib.h"
#include "Input/Input.h"
#include "Manager/Manager.h"
#include "Graphics/Texture/TexLoader.h"
#include <Windows.h>

#pragma comment(lib, "d3d12.lib")
#pragma comment(lib, "dxgi.lib")
#pragma comment(lib, "d3dcompiler.lib")

// ������
bool okmonn::Init(const Vec2& winSize, const Vec2& winPos, const std::string& parent)
{
	return Manager::Get().InitLib(winSize, winPos, parent);
}

// ���b�Z�[�W�m�F
bool okmonn::CheckMsg(void)
{
	static MSG msg{};

	if (msg.message == WM_QUIT)
	{
		return false;
	}

	//�Ăяo�����X���b�h�����L���Ă���E�B���h�E�ɑ��M���ꂽ���b�Z�[�W�ۗ̕�����Ă��镨���擾
	if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
	{
		//���z�L�[���b�Z�[�W�𕶎����b�Z�[�W�ɕϊ�
		TranslateMessage(&msg);
		//1�̃E�B�h�E�v���V�[�W���Ƀ��b�Z�[�W�𑗏o����
		DispatchMessage(&msg);
	}

	return true;
}

// �L�[����
bool okmonn::CheckKey(const KeyCode& key)
{
	return Input::Get().CheckKey(key);
}

// �g���K�[����
bool okmonn::Trigger(const KeyCode& key)
{
	return Input::Get().Trigger(key);
}

// �摜�ǂݍ���
int okmonn::LoadImg(const std::string& fileName)
{
	return Manager::Get().LoadImg(fileName);
}

// ��ʃN���A
void okmonn::Clear(void)
{
	Manager::Get().Clear();
}

// �{���̉摜�T�C�Y�ŕ`��
void okmonn::DrawImg(const int& id, const Vec2& pos, const float& angle, const bool& turnX, const bool& turnY, const float& alpha)
{
	Manager::Get().DrawImg(id, Vec2f(float(pos.x), float(pos.y)), angle, turnX, turnY, alpha);
}

// �w�肵���摜�T�C�Y�ŕ`��
void okmonn::DrawImgRect(const int& id, const Vec2& pos, const Vec2& size, const float& angle, const bool& turnX, const bool& turnY, const float& alpha)
{
	Manager::Get().DrawImgRect(id, Vec2f(float(pos.x), float(pos.y)), Vec2f(float(size.x), float(size.y)), angle, turnX, turnY, alpha);
}

// �w�肵���摜�T�C�Y�Ŏw�肵����`�ɕ������ĕ`��
void okmonn::DrawImgDivide(const int& id, const Vec2& pos, const Vec2& size, const Vec2& uvPos, const Vec2& uvSize, 
	const float& angle, const bool& turnX, const bool& turnY, const float& alpha)
{
	Manager::Get().DrawImgDivide(id, Vec2f(float(pos.x), float(pos.y)), Vec2f(float(size.x), float(size.y)), 
		Vec2f(float(uvPos.x), float(uvPos.y)), Vec2f(float(uvSize.x), float(uvSize.y)), angle, turnX, turnY, alpha);
}

// �|�C���g�`��
void okmonn::DrawPoint(const Vec2& pos, const float& r, const float& g, const float& b, const float& a)
{
	Manager::Get().DrawPoint(Vec2f(float(pos.x), float(pos.y)), r, g, b, a);
}

// ���C���`��
void okmonn::DrawLine(const Vec2& pos1, const Vec2& pos2, const float& r, const float& g, const float& b, const float& a)
{
	Manager::Get().DrawLine(Vec2f(float(pos1.x), float(pos1.y)), Vec2f(float(pos2.x), float(pos2.y)), r, g, b, a);
}

// �g���C�A���O���`��
void okmonn::DrawTriangle(const Vec2& pos1, const Vec2& pos2, const Vec2& pos3, const float& r, const float& g, const float& b, const float& a)
{
	Manager::Get().DrawTriangle(Vec2f(float(pos1.x), float(pos1.y)), Vec2f(float(pos2.x), float(pos2.y)), Vec2f(float(pos3.x), float(pos3.y)), r, g, b, a);
}

// �{�b�N�X�`��
void okmonn::DrawBox(const Vec2& pos, const Vec2& size, const float& r, const float& g, const float& b, const float& a)
{
	Manager::Get().DrawBox(Vec2f(float(pos.x), float(pos.y)), Vec2f(float(size.x), float(size.y)), r, g, b, a);
}

// ���s
void okmonn::Execution(void)
{
	Manager::Get().Execution();
}

// �^�[�Q�b�g�ɂ��郉�C�u������ς���
void okmonn::ChangeTargetName(const std::string& name)
{
	Manager::Get().ChangeTarget(name);
}

// ���݃^�[�Q�b�g�ɂ��Ă��郉�C�u�����ʖ����擾
std::string okmonn::GetNowTargetLibName(void)
{
	return Manager::Get().GetTarget();
}

// �e�N�X�`���n���h���폜
void okmonn::DeleteImg(const int& id)
{
	Manager::Get().DeleteTex(id);
}

// �v���~�e�B�u�f�[�^�폜
void okmonn::DeletePrim(const bool& memReset)
{
	Manager::Get().DeletePrim(memReset);
}

// �摜�f�[�^�폜
void okmonn::DeleteImg(const std::string& fileName)
{
	TexLoader::Get().Delete(fileName);
}
