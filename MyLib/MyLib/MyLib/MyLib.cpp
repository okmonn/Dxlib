#include "MyLib.h"
#include "Window/Window.h"
#include "Queue/Queue.h"
#include "List/List.h"
#include "Fence/Fence.h"
#include "Swap/Swap.h"
#include "Render/Render.h"
#include "Depth/Depth.h"
#include "etc/Release.h"
#include <Windows.h>

#pragma comment(lib, "d3d12.lib")
#pragma comment(lib, "dxgi.lib")
#pragma comment(lib, "d3dcompiler.lib")

// �R���X�g���N�^
MyLib::MyLib(const Vec2& size, const Vec2& pos) : winSize(size)
{
#ifdef _DEBUG
	ID3D12Debug* debug = nullptr;
	D3D12GetDebugInterface(IID_PPV_ARGS(&debug));
	debug->EnableDebugLayer();
#endif

	Instance(pos);
}

// �f�X�g���N�^
MyLib::~MyLib()
{
}

// �N���X�̃C���X�^���X��
void MyLib::Instance(const Vec2& pos)
{
	win    = std::make_shared<Window>(pos, winSize);
	queue  = std::make_shared<Queue>(D3D12_COMMAND_LIST_TYPE::D3D12_COMMAND_LIST_TYPE_DIRECT);
	list   = std::make_shared<List>(D3D12_COMMAND_LIST_TYPE::D3D12_COMMAND_LIST_TYPE_DIRECT);
	fence  = std::make_unique<Fence>(queue);
	swap   = std::make_shared<Swap>(win, queue, winSize);
	render = std::make_unique<Render>(swap);
	depth  = std::make_unique<Depth>(winSize);
}

// ���b�Z�[�W�̊m�F
bool MyLib::CheckMsg(void) const
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

// �N���A
void MyLib::Clear(void) const
{
	list->Reset();

	list->Viewport(winSize);
	list->Scissor(winSize);

	list->Barrier(D3D12_RESOURCE_STATES::D3D12_RESOURCE_STATE_PRESENT, D3D12_RESOURCE_STATES::D3D12_RESOURCE_STATE_RENDER_TARGET, render->Get());

	render->Clear(list, depth->Get());

	depth->Clear(list);
}

// ���s
void MyLib::Execution(void) const
{
	list->Barrier(D3D12_RESOURCE_STATES::D3D12_RESOURCE_STATE_RENDER_TARGET, D3D12_RESOURCE_STATES::D3D12_RESOURCE_STATE_PRESENT, render->Get());

	list->Close();

	ID3D12CommandList* com[] = {
		list->GetList()
	};

	queue->Execution(com, _countof(com));

	swap->Present();

	fence->Wait();
}
