#include "Texture.h"
#include "TexLoader.h"
#include "../List/List.h"
#include "../etc/Release.h"

#define RSC_MAX 2
#define VERTEX_MAX 4

std::vector<Vertex> Texture::vertex = std::vector<Vertex>(VERTEX_MAX);

// コンストラクタ
Texture::Texture() : 
	heap(nullptr), constant(nullptr), data(nullptr)
{
	rsc.resize(RSC_MAX + 1);
}

// デストラクタ
Texture::~Texture()
{
	Desc.UnMap((*rsc.rbegin()));
	Desc.UnMap((*rsc.begin()));
	Release((*rsc.begin()));
	Release((*rsc.rbegin()));
	Release(heap);
}

// 読み込み
int Texture::Load(const std::string & fileName)
{
	if (FAILED(TexLoader::Get().Load(fileName)))
	{
		return -1;
	}

	size             = TexLoader::Get().GetSize(fileName);
	uvSize           = size;
	rsc[RSC_MAX - 1] = TexLoader::Get().GetRsc(fileName);
	this->fileName   = fileName;

	Init();

	return 0;
}

// テクスチャサイズ取得
Vec2f Texture::GetTexSize(void) const
{
	return TexLoader::Get().GetSize(fileName);
}

// 定数リソース生成
long Texture::CreateConstant(void)
{
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

	return Desc.CreateRsc(&(*rsc.begin()), prop, desc, nullptr, D3D12_RESOURCE_STATES::D3D12_RESOURCE_STATE_GENERIC_READ);
}

// 頂点リソース生成
long Texture::CreateVertex(void)
{
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
	desc.Width            = sizeof(vertex[0]) * vertex.size();

	return Desc.CreateRsc(&(*rsc.rbegin()), prop, desc, nullptr, D3D12_RESOURCE_STATES::D3D12_RESOURCE_STATE_GENERIC_READ);
}

// サブリソース書き込み
long Texture::WriteSub(const uint& index)
{
	D3D12_BOX box{};
	box.back   = 1;
	box.bottom = rsc[index]->GetDesc().Height;
	box.right  = uint(rsc[index]->GetDesc().Width);

	auto hr = rsc[index]->WriteToSubresource(0, &box, &TexLoader::Get().GetDecode(fileName)[0], uint(TexLoader::Get().GetSub(fileName).RowPitch), uint(TexLoader::Get().GetSub(fileName).SlicePitch));
	if (FAILED(hr))
	{
		OutputDebugString(_T("\nサブリソース書き込み：失敗\n"));
	}

	return hr;
}

// 初期化
void Texture::Init(void)
{
	Desc.CreateHeap(&heap, D3D12_DESCRIPTOR_HEAP_TYPE::D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV, D3D12_DESCRIPTOR_HEAP_FLAGS::D3D12_DESCRIPTOR_HEAP_FLAG_SHADER_VISIBLE, RSC_MAX);

	CreateConstant();
	CreateVertex();

	uint index = 0;
	Desc.CBV(heap, rsc[index], index);
	Desc.Map(rsc[index], (void**)(&constant));

	++index;
	Desc.SRV(heap, rsc[index], index);
	WriteSub(index);

	++index;
	Desc.Map(rsc[index], &data);
}

// 描画準備
uint Texture::SetDraw(std::weak_ptr<List>list)
{
	constant->uvPos   = uvPos;
	constant->uvSize  = uvSize;
	constant->reverse = Vec2f(float(reverse.x), float(reverse.y));

	D3D12_VERTEX_BUFFER_VIEW view{};
	view.BufferLocation = (*rsc.rbegin())->GetGPUVirtualAddress();
	view.SizeInBytes    = uint((*rsc.rbegin())->GetDesc().Width);
	view.StrideInBytes  = sizeof(vertex[0]);
	list.lock()->VertexView(view);

	auto index = 0;
	list.lock()->Heap(&heap, 1);
	for (uint i = 0; i < RSC_MAX; ++i)
	{
		list.lock()->GraphicTable(i, heap, i);
		index = i;
	}

	return ++index;
}

// 頂点数取得
uint Texture::GetVertexNum(void) const
{
	return uint(vertex.size());
}
