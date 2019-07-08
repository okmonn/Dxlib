#include "Window.h"
#include "../../resource.h"
#include <tchar.h>
#include <crtdbg.h>
#include <Windows.h>

// コンストラクタ
Window::Window(const Vec2& pos, const Vec2& size, void* parent) :
	handle(nullptr), instance(nullptr), name(nullptr)
{
	CreateWnd(pos, size, parent);
}

// デストラクタ
Window::~Window()
{
	DestroyWindow(HWND(handle));
	UnregisterClass(name, HINSTANCE(instance));
}

// ウィンドウコールバック
#ifdef _WIN64
__int64 __stdcall Window::WindowProc(void* hWnd, unsigned int message, unsigned __int64 wParam, __int64 lParam)
#else
long __stdcall Window::WindowProc(void* hWnd, unsigned int message, unsigned int wParam, long lParam)
#endif
{
	switch (message)
	{
	case WM_MOUSEWHEEL:
		break;
	case WM_DESTROY:
		if (GetParent(HWND(hWnd)) != nullptr)
		{
			break;
		}
		PostQuitMessage(0);
		return 0;
	case WM_DROPFILES:
		//ウィンドウをアクティブにする
		SetForegroundWindow(HWND(hWnd));
		break;
	default:
		break;
	}

	return DefWindowProc(HWND(hWnd), message, wParam, lParam);
}

// ウィンドウ生成
void Window::CreateWnd(const Vec2& pos, const Vec2& size, void* parent)
{
	WNDCLASSEX wnd{};
	wnd.cbSize        = sizeof(WNDCLASSEX);
	wnd.hbrBackground = CreateSolidBrush(COLOR_APPWORKSPACE);
	wnd.hCursor       = LoadCursor(nullptr, IDC_ARROW);
	wnd.hIcon         = LoadIcon(GetModuleHandle(0), MAKEINTRESOURCE(AVICII));
	wnd.hIconSm       = LoadIcon(GetModuleHandle(0), MAKEINTRESOURCE(AVICII));
	wnd.hInstance     = GetModuleHandle(0);
	wnd.lpfnWndProc   = WNDPROC(WindowProc);
	wnd.lpszClassName = _T("おかもん");
	wnd.lpszMenuName  = _T("おかもん");
	wnd.style         = CS_HREDRAW | CS_VREDRAW;
	RegisterClassEx(&wnd);

	auto flag = (parent == nullptr) ? (WS_OVERLAPPEDWINDOW) : (WS_OVERLAPPEDWINDOW | WS_POPUP);

	RECT rect{};
	rect.bottom = static_cast<long>(size.y);
	rect.right  = static_cast<long>(size.x);
	AdjustWindowRect(&rect, flag, false);

	handle = CreateWindowEx(WS_EX_ACCEPTFILES, wnd.lpszClassName, _T("おかもん"), flag, pos.x, pos.y,
		(rect.right - rect.left), (rect.bottom - rect.top), HWND(parent), nullptr, wnd.hInstance, nullptr);
	_ASSERT(handle != nullptr);

	instance = wnd.hInstance;
	name     = wnd.lpszClassName;

	ShowWindow(reinterpret_cast<HWND>(handle), SW_SHOW);
}

// ウィンドウハンドル取得
void* Window::Get(void) const
{
	return handle;
}
