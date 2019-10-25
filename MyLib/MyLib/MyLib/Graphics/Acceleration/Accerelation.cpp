#include "Accerelation.h"
#include "../Device/Device.h"
#include "../List/List.h"
#include <d3d12.h>

// コンストラクタ
Acceleration::Acceleration(std::weak_ptr<List>list) :
	list(list)
{
}

// デストラクタ
Acceleration::~Acceleration()
{
}

// トップレベル構造生成
void Acceleration::CreateTop(void)
{
}

// ボトムレベル構造生成
void Acceleration::CreateBottom(ID3D12Resource* vertex, const size_t& stride)
{
	D3D12_RAYTRACING_GEOMETRY_DESC desc{};
	desc.Flags                                = D3D12_RAYTRACING_GEOMETRY_FLAGS::D3D12_RAYTRACING_GEOMETRY_FLAG_OPAQUE;
	desc.Triangles.VertexBuffer.StartAddress  = vertex->GetGPUVirtualAddress;
	desc.Triangles.VertexBuffer.StrideInBytes = stride;
	desc.Triangles.VertexFormat               = DXGI_FORMAT_R32G32B32_FLOAT;
	desc.Triangles.VertexCount                = 3;
	desc.Type                                 = D3D12_RAYTRACING_GEOMETRY_TYPE::D3D12_RAYTRACING_GEOMETRY_TYPE_TRIANGLES;

	D3D12_BUILD_RAYTRACING_ACCELERATION_STRUCTURE_INPUTS input{};
	input.DescsLayout    = D3D12_ELEMENTS_LAYOUT::D3D12_ELEMENTS_LAYOUT_ARRAY;
	input.Flags          = D3D12_RAYTRACING_ACCELERATION_STRUCTURE_BUILD_FLAGS::D3D12_RAYTRACING_ACCELERATION_STRUCTURE_BUILD_FLAG_NONE;
	input.NumDescs       = 1;
	input.pGeometryDescs = &desc;
	input.Type           = D3D12_RAYTRACING_ACCELERATION_STRUCTURE_TYPE::D3D12_RAYTRACING_ACCELERATION_STRUCTURE_TYPE_BOTTOM_LEVEL;

	D3D12_RAYTRACING_ACCELERATION_STRUCTURE_PREBUILD_INFO info{};
	Device::Get().Dev()->GetRaytracingAccelerationStructurePrebuildInfo(&input, &info);
}
