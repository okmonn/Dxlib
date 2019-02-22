#pragma once
#include "../Vector/Vector2.h"

class Window
{
public:
	// �R���X�g���N�^
	inline Window(const Vec2& pos, const Vec2& size, void* parent = nullptr);
	// �f�X�g���N�^
	~Window();

	// �n���h���̎擾
	inline void* Get(void) const;

private:
	// �E�B���h�E�̃R�[���o�b�N
#ifdef _WIN64
	static __int64 __stdcall WindowProc(void* hWnd, unsigned int message, unsigned __int64 wParam, __int64 lParam);
#else
	static long __stdcall WindowProc(void* hWnd, unsigned int message, unsigned int wParam, long lParam);
#endif

	// �E�B���h�E����
	int CreateWnd(const Vec2& pos, const Vec2& size, void* parent);


	// �E�B���h�E�n���h��
	void* handle;

	// �E�B���h�E�C���X�^���X
	void* instance;

	// �E�B���h�E��
	const wchar_t* name;
};
