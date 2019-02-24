#pragma once
#include "../Vector/Vector2.h"
#include "../etc/Define.h"
#include <string>
#include <optional>

class Window
{
public:
	// �R���X�g���N�^
	Window(const Vec2& pos, const Vec2& size, void* parent = nullptr);
	// �f�X�g���N�^
	~Window();

	// �n���h���擾
	void* Get(void) const;
	// �h���b�v�t�@�C���擾
	std::optional<std::string> GetDrop(void);

private:
	// �E�B���h�E�R�[���o�b�N
#ifdef _WIN64
	static __int64 __stdcall WindowProc(void* hWnd, uint message, uint64 wParam, int64 lParam);
#else
	static long __stdcall WindowProc(void* hWnd, uint message, uint wParam, long lParam);
#endif

	// �E�B���h�E����
	int CreateWnd(const Vec2& pos, const Vec2& size, void* parent);


	// �E�B���h�E�n���h��
	void* handle;

	// �E�B���h�E�C���X�^���X
	void* instance;

	// �E�B���h�E��
	const wchar_t* name;

	// �h���b�v�t�@�C����
	static std::optional<std::string>dropFile;
};
