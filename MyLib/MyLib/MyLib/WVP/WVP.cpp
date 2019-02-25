#include "WVP.h"
#include "../etc/Func.h"
#include "../etc/Release.h"

// コンストラクタ
WVP::WVP() : 
	heap(nullptr), rsc(nullptr), constant(nullptr), fov(0.0f)
{
	Init();
}

// デストラクタ
WVP::~WVP()
{
	Desc.UnMap(rsc);
	Release(rsc);
	Release(heap);
}

// 初期化
void WVP::Init(void)
{
	Desc.CreateHeap(&heap, D3D12_DESCRIPTOR_HEAP_TYPE::D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV, D3D12_DESCRIPTOR_HEAP_FLAGS::D3D12_DESCRIPTOR_HEAP_FLAG_SHADER_VISIBLE);

	D3D12_HEAP_PROPERTIES prop{};
	prop.CPUPageProperty      = D3D12_CPU_PAGE_PROPERTY::D3D12_CPU_PAGE_PROPERTY_UNKNOWN;
	prop.MemoryPoolPreference = D3D12_MEMORY_POOL::D3D12_MEMORY_POOL_UNKNOWN;
	prop.Type                 = D3D12_HEAP_TYPE::D3D12_HEAP_TYPE_UPLOAD;

	D3D12_RESOURCE_DESC desc{};
	desc.DepthOrArraySize = 1;
	desc.Dimension        = D3D12_RESOURCE_DIMENSION::D3D12_RESOURCE_DIMENSION_BUFFER;
	desc.Flags            = D3D12_RESOURCE_FLAGS::D3D12_RESOURCE_FLAG_NONE;
	desc.Format           = DXGI_FORMAT::DXGI_FORMAT_UNKNOWN;
	desc.Height           = 1;
	desc.Layout           = D3D12_TEXTURE_LAYOUT::D3D12_TEXTURE_LAYOUT_ROW_MAJOR;
	desc.MipLevels        = 1;
	desc.SampleDesc       = { 1, 0 };
	desc.Width            = (sizeof(Constant) + 0xff) &~0xff;

	Desc.CreateRsc(&rsc, prop, desc, nullptr, D3D12_RESOURCE_STATES::D3D12_RESOURCE_STATE_GENERIC_READ);

	Desc.CBV(heap, rsc);

	Desc.Map(rsc, (void**)(&constant));

	DirectX::XMStoreFloat4x4(&constant->world, DirectX::XMMatrixIdentity());
	DirectX::XMStoreFloat4x4(&constant->view, DirectX::XMMatrixIdentity());
	DirectX::XMStoreFloat4x4(&constant->projection, DirectX::XMMatrixIdentity());
}

// カメラセット
void WVP::SetCamera(const Vec3f& pos, const Vec3f& target, const Vec3f& upper, const Vec2f& winSize, const float& fov)
{
	this->pos     = pos;
	this->target  = target;
	this->upper   = upper;
	this->winSize = winSize;
	this->fov     = fov;
}

// カメラ行列セット
void WVP::SetCamera(void)
{
	DirectX::XMStoreFloat4x4(&constant->world, DirectX::XMMatrixIdentity());

	DirectX::XMStoreFloat4x4(&constant->view, DirectX::XMMatrixLookAtLH(DirectX::XMLoadFloat3(&DirectX::XMFLOAT3(pos.x, pos.y, pos.z)),
		DirectX::XMLoadFloat3(&DirectX::XMFLOAT3(target.x, target.y, target.z)),
		DirectX::XMLoadFloat3(&DirectX::XMFLOAT3(upper.x, upper.y, upper.z))));

	DirectX::XMStoreFloat4x4(&constant->projection, DirectX::XMMatrixPerspectiveFovLH(fov,
		winSize.x / winSize.y, 0.5f, 500.0f));
}
