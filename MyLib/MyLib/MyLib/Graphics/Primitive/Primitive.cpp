#include "Primitive.h"
#include "../List/List.h"
#include "../Descriptor/Descriptor.h"
#include <d3d12.h>

// コンストラクタ
Primitive::Primitive(std::weak_ptr<List>list, const okmonn::PrimType& type) :
	list(list), heap(nullptr), vRsc(nullptr), cRsc(nullptr), color(nullptr)
{
	vertex.resize(int(type));
	Init();
}

// デストラクタ
Primitive::~Primitive()
{
	okmonn::UnMap(cRsc.Get());
}

// 頂点リソース生成
void Primitive::CreateVRsc(void)
{
	D3D12_HEAP_PROPERTIES prop{};
	prop.Type = D3D12_HEAP_TYPE::D3D12_HEAP_TYPE_UPLOAD;

	D3D12_RESOURCE_DESC desc{};
	desc.DepthOrArraySize = 1;
	desc.Dimension        = D3D12_RESOURCE_DIMENSION::D3D12_RESOURCE_DIMENSION_BUFFER;
	desc.Height           = 1;
	desc.Layout           = D3D12_TEXTURE_LAYOUT::D3D12_TEXTURE_LAYOUT_ROW_MAJOR;
	desc.MipLevels        = 1;
	desc.SampleDesc       = { 1, 0 };
	desc.Width            = unsigned __int64(sizeof(vertex[0]) * vertex.size());

	okmonn::CreateRsc(&vRsc, prop, desc, nullptr, D3D12_RESOURCE_STATES::D3D12_RESOURCE_STATE_GENERIC_READ);
}

// 定数リソース生成
void Primitive::CreateCRsc(void)
{
	D3D12_HEAP_PROPERTIES prop{};
	prop.Type = D3D12_HEAP_TYPE::D3D12_HEAP_TYPE_UPLOAD;

	D3D12_RESOURCE_DESC desc{};
	desc.DepthOrArraySize = 1;
	desc.Dimension        = D3D12_RESOURCE_DIMENSION::D3D12_RESOURCE_DIMENSION_BUFFER;
	desc.Height           = 1;
	desc.Layout           = D3D12_TEXTURE_LAYOUT::D3D12_TEXTURE_LAYOUT_ROW_MAJOR;
	desc.MipLevels        = 1;
	desc.SampleDesc       = { 1, 0 };
	desc.Width            = (sizeof(okmonn::Color) + 0xff) & ~0xff;

	okmonn::CreateRsc(&cRsc, prop, desc, nullptr, D3D12_RESOURCE_STATES::D3D12_RESOURCE_STATE_GENERIC_READ);
	okmonn::CBV(cRsc.Get(), heap.Get());
	okmonn::Map(cRsc.Get(), (void**)&color);
}

// 初期化
void Primitive::Init(void)
{
	okmonn::CreateHeap(&heap, D3D12_DESCRIPTOR_HEAP_TYPE::D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV, 
		D3D12_DESCRIPTOR_HEAP_FLAGS::D3D12_DESCRIPTOR_HEAP_FLAG_SHADER_VISIBLE);

	CreateVRsc();
	CreateCRsc();
}

// ポイント描画
void Primitive::DrawPoint(const Vec2f& pos, const okmonn::Color& color)
{
	vertex[0] = pos;

	void* data = nullptr;
	okmonn::Map(vRsc.Get(), &data);
	memcpy(data, vertex.data(), sizeof(vertex[0]) * vertex.size());
	okmonn::UnMap(vRsc.Get());

	(*this->color) = color;

	list.lock()->Get()->IASetPrimitiveTopology(D3D12_PRIMITIVE_TOPOLOGY::D3D_PRIMITIVE_TOPOLOGY_POINTLIST);
}

// ライン描画
void Primitive::DrawLine(const Vec2f& pos1, const Vec2f& pos2, const okmonn::Color& color)
{
	vertex[0] = pos1;
	vertex[1] = pos2;

	void* data = nullptr;
	okmonn::Map(vRsc.Get(), &data);
	memcpy(data, vertex.data(), sizeof(vertex[0]) * vertex.size());
	okmonn::UnMap(vRsc.Get());

	(*this->color) = color;

	list.lock()->Get()->IASetPrimitiveTopology(D3D12_PRIMITIVE_TOPOLOGY::D3D_PRIMITIVE_TOPOLOGY_LINELIST);
}

// トライアングル描画
void Primitive::DrawTriangle(const Vec2f& pos1, const Vec2f& pos2, const Vec2f& pos3, const okmonn::Color& color)
{
	vertex[0] = pos1;
	vertex[1] = pos2;
	vertex[2] = pos3;

	void* data = nullptr;
	okmonn::Map(vRsc.Get(), &data);
	memcpy(data, vertex.data(), sizeof(vertex[0]) * vertex.size());
	okmonn::UnMap(vRsc.Get());

	(*this->color) = color;

	list.lock()->Get()->IASetPrimitiveTopology(D3D12_PRIMITIVE_TOPOLOGY::D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
}

// ボックス描画
void Primitive::DrawBox(const Vec2f& pos, const Vec2f& size, const okmonn::Color& color)
{
	vertex[0] = pos;
	vertex[1] = Vec2f(pos.x + size.x, pos.y);
	vertex[2] = Vec2f(pos.x, pos.y + size.y);
	vertex[3] = pos + size;

	void* data = nullptr;
	okmonn::Map(vRsc.Get(), &data);
	memcpy(data, vertex.data(), sizeof(vertex[0]) * vertex.size());
	okmonn::UnMap(vRsc.Get());

	(*this->color) = color;

	list.lock()->Get()->IASetPrimitiveTopology(D3D12_PRIMITIVE_TOPOLOGY::D3D_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);
}

// 描画
void Primitive::Draw()
{
	D3D12_VERTEX_BUFFER_VIEW desc{};
	desc.BufferLocation = vRsc->GetGPUVirtualAddress();
	desc.SizeInBytes    = unsigned int(vRsc->GetDesc().Width);
	desc.StrideInBytes  = sizeof(vertex[0]);
	list.lock()->Get()->IASetVertexBuffers(0, 1, &desc);

	list.lock()->Get()->SetDescriptorHeaps(1, heap.GetAddressOf());

	list.lock()->SetGraphicsTable(1, heap.Get());

	list.lock()->Get()->DrawInstanced(unsigned int(vertex.size()), 1, 0, 0);
}
