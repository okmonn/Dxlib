#pragma once
#include "../Vector/Vector2.h"
#include "../etc/Define.h"
#include <string>
#include <optional>

class Window
{
public:
	// コンストラクタ
	Window(const Vec2& pos, const Vec2& size, void* parent = nullptr);
	// デストラクタ
	~Window();

	// ハンドル取得
	void* Get(void) const;
	// ドロップファイル取得
	std::optional<std::string> GetDrop(void);

private:
	// ウィンドウコールバック
#ifdef _WIN64
	static __int64 __stdcall WindowProc(void* hWnd, uint message, uint64 wParam, int64 lParam);
#else
	static long __stdcall WindowProc(void* hWnd, uint message, uint wParam, long lParam);
#endif

	// ウィンドウ生成
	int CreateWnd(const Vec2& pos, const Vec2& size, void* parent);


	// ウィンドウハンドル
	void* handle;

	// ウィンドウインスタンス
	void* instance;

	// ウィンドウ名
	const wchar_t* name;

	// ドロップファイル名
	static std::optional<std::string>dropFile;
};
