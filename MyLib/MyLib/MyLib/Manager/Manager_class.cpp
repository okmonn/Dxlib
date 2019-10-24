#include "Manager.h"
#include "../Window/Window.h"
#include "../Graphics/Device/Device.h"
#include "../Graphics/Queue/Queue.h"
#include "../Graphics/Allocator/Allocator.h"
#include "../Graphics/List/List.h"
#include "../Graphics/Fence/Fence.h"
#include "../Graphics/Swap/Swap.h"
#include "../Graphics/Render/Render.h"
#include "../Graphics/Descriptor/Descriptor.h"
#include <Windows.h>
#include <d3d12.h>
#include <dxgi1_6.h>

// �R���X�g���N�^
MyLib::MyLib(const Vec2& size, const Vec2& pos, MyLib* parent) : 
	allo(Swap::bufferCnt)
{
	void* tmp = (parent == nullptr) ? nullptr : parent->win->Get();
	win = std::make_shared<Window>(pos, size, tmp);

	Init();
}

// �f�X�g���N�^
MyLib::~MyLib()
{
	okmonn::UnMap(rsc.Get());
}

// �萔���\�[�X����
void MyLib::CreateRsc(void)
{
	D3D12_HEAP_PROPERTIES prop{};
	prop.Type = D3D12_HEAP_TYPE::D3D12_HEAP_TYPE_UPLOAD;

	D3D12_RESOURCE_DESC desc{};
	desc.DepthOrArraySize = 1;
	desc.Dimension = D3D12_RESOURCE_DIMENSION::D3D12_RESOURCE_DIMENSION_BUFFER;
	desc.Height = 1;
	desc.Layout = D3D12_TEXTURE_LAYOUT::D3D12_TEXTURE_LAYOUT_ROW_MAJOR;
	desc.MipLevels = 1;
	desc.SampleDesc = { 1, 0 };
	desc.Width = (sizeof(Vec2f) + 0xff) & ~0xff;

	okmonn::CreateRsc(&rsc, prop, desc, nullptr, D3D12_RESOURCE_STATES::D3D12_RESOURCE_STATE_GENERIC_READ);
	okmonn::CBV(rsc.Get(), heap.Get());
	okmonn::Map(rsc.Get(), (void**)& data);

	data->x = float(GetWinSize().x);
	data->y = float(GetWinSize().y);
}

// ������
void MyLib::Init(void)
{
	okmonn::CreateHeap(&heap, D3D12_DESCRIPTOR_HEAP_TYPE::D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV,
		D3D12_DESCRIPTOR_HEAP_FLAGS::D3D12_DESCRIPTOR_HEAP_FLAG_SHADER_VISIBLE);
	CreateRsc();

	queue  = std::make_shared<Queue>(D3D12_COMMAND_LIST_TYPE::D3D12_COMMAND_LIST_TYPE_DIRECT);
	for (auto& i : allo)
	{
		i  = std::make_shared<Allocator>(D3D12_COMMAND_LIST_TYPE::D3D12_COMMAND_LIST_TYPE_DIRECT);
	}
	list   = std::make_shared<List>(allo[0], D3D12_COMMAND_LIST_TYPE::D3D12_COMMAND_LIST_TYPE_DIRECT);
	fence  = std::make_shared<Fence>(queue);
	swap   = std::make_shared<Swap>(win, queue);
	render = std::make_shared<Render>(swap);
}

// ��ʃN���A
void MyLib::Clear(void)
{
	unsigned int index = swap->Get()->GetCurrentBackBufferIndex();

	//�R�}���h�֘A�̃��Z�b�g
	auto hr = allo[index]->Get()->Reset();
	_ASSERTE(hr == S_OK);
	hr = list->Get()->Reset(allo[index]->Get(), nullptr);
	_ASSERTE(hr == S_OK);

	//�`����Z�b�g
	list->Viewport(GetWinSize());
	list->Scissor(GetWinSize());

	//�`��^�[�Q�b�g�X�V
	list->Barrier(render->Get(), D3D12_RESOURCE_STATES::D3D12_RESOURCE_STATE_PRESENT, D3D12_RESOURCE_STATES::D3D12_RESOURCE_STATE_RENDER_TARGET);

	//�`���ʃN���A
	render->Clear(list);
}

// ���s
void MyLib::Execution(void)
{
	//�`��^�[�Q�b�g�X�V
	list->Barrier(render->Get(), D3D12_RESOURCE_STATES::D3D12_RESOURCE_STATE_RENDER_TARGET, D3D12_RESOURCE_STATES::D3D12_RESOURCE_STATE_PRESENT);

	auto hr = list->Get()->Close();
	_ASSERT(hr == S_OK);

	ID3D12CommandList* com[] = {
		list->Get()
	};

	//�R�}���h���s
	queue->Get()->ExecuteCommandLists(_countof(com), com);

	//���E�\��ʔ��]
	swap->Get()->Present(0, 0);

	fence->Wait();
}

// �`�揀��
void MyLib::SetDraw(const size_t& index)
{
	list->Get()->SetDescriptorHeaps(1, heap.GetAddressOf());

	auto handle = heap->GetGPUDescriptorHandleForHeapStart();
	handle.ptr += unsigned __int64(Device::Get().Dev()->GetDescriptorHandleIncrementSize(heap->GetDesc().Type) * index);
	list->Get()->SetGraphicsRootDescriptorTable(unsigned int(index), handle);
}

// �E�B���h�E�T�C�Y�擾
Vec2 MyLib::GetWinSize(void)
{
	RECT winSize{};
	GetClientRect(HWND(win->Get()), &winSize);

	return Vec2(int(winSize.right), int(winSize.bottom));
}

// �R�}���h���X�g�擾
std::weak_ptr<List> MyLib::GetList(void) const
{
	return list;
}
