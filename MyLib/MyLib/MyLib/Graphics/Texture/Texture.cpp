#include "Texture.h"
#include "TexLoader.h"
#include "../Descriptor/Descriptor.h"
#include "../List/List.h"
#include <d3d12.h>

// コンストラクタ
Texture::Texture() : 
	heap(nullptr), vRsc(nullptr), constant(nullptr), data(nullptr), index(0)
{
	Init();
}

// コンストラクタ
Texture::Texture(const std::string& fileName) : 
	heap(nullptr), vRsc(nullptr), constant(nullptr), data(nullptr), index(0)
{
	Init();
	Load(fileName);
}

// デストラクタ
Texture::~Texture()
{
	okmonn::UnMap(cRsc.rsc.Get());
	okmonn::UnMap(vRsc.Get());
}

// 頂点リソース生成
void Texture::CreateVRsc(void)
{
	D3D12_HEAP_PROPERTIES prop{};
	prop.Type                 = D3D12_HEAP_TYPE::D3D12_HEAP_TYPE_UPLOAD;

	D3D12_RESOURCE_DESC desc{};
	desc.DepthOrArraySize = 1;
	desc.Dimension        = D3D12_RESOURCE_DIMENSION::D3D12_RESOURCE_DIMENSION_BUFFER;
	desc.Height           = 1;
	desc.Layout           = D3D12_TEXTURE_LAYOUT::D3D12_TEXTURE_LAYOUT_ROW_MAJOR;
	desc.MipLevels        = 1;
	desc.SampleDesc       = { 1, 0 };
	desc.Width            = sizeof(vertex[0]) * vertex.size();

	okmonn::CreateRsc(&vRsc, prop, desc, nullptr, D3D12_RESOURCE_STATES::D3D12_RESOURCE_STATE_GENERIC_READ);
	okmonn::Map(vRsc.Get(), &data);
}

// 定数リソース生成
void Texture::CreateCRsc(void)
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
	desc.Width            = (sizeof(Constant) + 0xff) & ~0xff;

	okmonn::CreateRsc(&cRsc.rsc, prop, desc, nullptr, D3D12_RESOURCE_STATES::D3D12_RESOURCE_STATE_GENERIC_READ);
	cRsc.index = index++;

	okmonn::CBV(cRsc.rsc.Get(), heap.Get(), cRsc.index);
	okmonn::Map(cRsc.rsc.Get(), (void**)(&constant));
}

// 初期化
void Texture::Init(void)
{
	okmonn::CreateHeap(heap.GetAddressOf(), D3D12_DESCRIPTOR_HEAP_TYPE::D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV,
		D3D12_DESCRIPTOR_HEAP_FLAGS::D3D12_DESCRIPTOR_HEAP_FLAG_SHADER_VISIBLE, 2);
	vertex.resize(4);

	CreateVRsc();
	CreateCRsc();
}

// 読み込み
void Texture::Load(const std::string& fileName)
{
	TexLoader::Get().Load(fileName);
	okmonn::SRV(TexLoader::Get().Rsc(fileName), heap.Get(), index++);

	constant->size = TexLoader::Get().GetSize(fileName);
}

// 本来のサイズで描画
void Texture::DrawImg(const Vec2f& pos, const float& angle, const bool& turnX, const bool& turnY, const float& alpha)
{
	vertex[0] = { pos,                                      0.0f };
	vertex[1] = { Vec2f(pos.x + constant->size.x, pos.y), { constant->size.x, 0.0f } };
	vertex[2] = { Vec2f(pos.x, pos.y + constant->size.y), { 0.0f, constant->size.y } };
	vertex[3] = { pos + constant->size,                     constant->size };
	memcpy(data, vertex.data(), sizeof(vertex[0]) * vertex.size());

	constant->reverse.x = (turnX == true) ? 1.0f : 0.0f;
	constant->reverse.y = (turnY == true) ? 1.0f : 0.0f;
	constant->angle     = angle;
	constant->alpha     = alpha;
}

// 指定したサイズで描画
void Texture::DrawRect(const Vec2f& pos, const Vec2f& size, const float& angle, const bool& turnX, const bool& turnY, const float& alpha)
{
	vertex[0] = { pos,                            0.0f };
	vertex[1] = { Vec2f(pos.x + size.x, pos.y), { constant->size.x, 0.0f } };
	vertex[2] = { Vec2f(pos.x, pos.y + size.y), { 0.0f, constant->size.y } };
	vertex[3] = { pos + size,                     constant->size };
	memcpy(data, vertex.data(), sizeof(vertex[0]) * vertex.size());

	constant->reverse.x = (turnX == true) ? 1.0f : 0.0f;
	constant->reverse.y = (turnY == true) ? 1.0f : 0.0f;
	constant->angle     = angle;
	constant->alpha     = alpha;
}

// 指定したサイズで分割描画
void Texture::DrawDivide(const Vec2f& pos, const Vec2f& size, const Vec2f& uvPos, const Vec2f& uvSize, 
	const float& angle, const bool& turnX, const bool& turnY, const float& alpha)
{
	vertex[0] = { pos,                            uvPos };
	vertex[1] = { Vec2f(pos.x + size.x, pos.y), { uvPos.x + uvSize.x, uvPos.y } };
	vertex[2] = { Vec2f(pos.x, pos.y + size.y), { uvPos.x,            uvPos.y + uvSize.y } };
	vertex[3] = { pos + size,                     uvPos + uvSize };
	memcpy(data, vertex.data(), sizeof(vertex[0]) * vertex.size());

	constant->reverse.x = (turnX == true) ? 1.0f : 0.0f;
	constant->reverse.y = (turnY == true) ? 1.0f : 0.0f;
	constant->angle     = angle;
	constant->alpha     = alpha;
}

// 描画
void Texture::Draw(std::weak_ptr<List> list)
{
	D3D12_VERTEX_BUFFER_VIEW desc{};
	desc.BufferLocation = vRsc->GetGPUVirtualAddress();
	desc.SizeInBytes    = unsigned int(vRsc->GetDesc().Width);
	desc.StrideInBytes  = sizeof(vertex[0]);
	list.lock()->Get()->IASetVertexBuffers(0, 1, &desc);

	list.lock()->Get()->SetDescriptorHeaps(1, heap.GetAddressOf());

	for (unsigned char i = cRsc.index; i < index; ++i)
	{
		list.lock()->SetGraphicsTable(i + 1, heap.Get(), i);
	}

	list.lock()->Get()->IASetPrimitiveTopology(D3D12_PRIMITIVE_TOPOLOGY::D3D_PRIMITIVE_TOPOLOGY_LINELIST_ADJ);

	list.lock()->Get()->DrawInstanced(unsigned int(vertex.size()), 1, 0, 0);
}
