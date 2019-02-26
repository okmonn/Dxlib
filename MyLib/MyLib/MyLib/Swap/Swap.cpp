#include "Swap.h"
#include "../Window/Window.h"
#include "../Queue/Queue.h"
#include "../etc/Func.h"
#include "../etc/Release.h"

// �o�b�N�o�b�t�@��
#define BACK_BUFFER 2

// �R���X�g���N�^
Swap::Swap(std::weak_ptr<Window>win, std::weak_ptr<Queue>queue, const Vec2& size)
{
	CreateSwap(win, queue, size);
}

// �f�X�g���N�^
Swap::~Swap()
{
	Release(swap);
}

// �X���b�v�`�F�C������
long Swap::CreateSwap(std::weak_ptr<Window> win, std::weak_ptr<Queue> queue, const Vec2& size)
{
	DXGI_SWAP_CHAIN_DESC1 desc{};
	desc.AlphaMode   = DXGI_ALPHA_MODE::DXGI_ALPHA_MODE_UNSPECIFIED;
	desc.BufferCount = BACK_BUFFER;
	desc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	desc.Format      = DXGI_FORMAT::DXGI_FORMAT_R8G8B8A8_UNORM;
	desc.Height      = uint(size.y);
	desc.SampleDesc  = { 1, 0 };
	desc.Scaling     = DXGI_SCALING::DXGI_SCALING_STRETCH;
	desc.Stereo      = false;
	desc.SwapEffect  = DXGI_SWAP_EFFECT::DXGI_SWAP_EFFECT_FLIP_DISCARD;
	desc.Width       = uint(size.x);

	auto hr = Factory->CreateSwapChainForHwnd(queue.lock()->Get(), HWND(win.lock()->Get()), &desc, nullptr, nullptr,(IDXGISwapChain1**)(&swap));
	if (FAILED(hr))
	{
		func::DebugLog("�X���b�v�`�F�C�������F���s");
	}

	return hr;
}

// ���E�\��ʂ̑J��
void Swap::Present(void) const
{
	swap->Present(1, 0);
}

// �X���b�v�`�F�C���擾
IDXGISwapChain4 * Swap::Get(void) const
{
	return swap;
}
