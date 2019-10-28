#include "Accerelation.h"
#include "../Device/Device.h"
#include "../List/List.h"
#include "../Descriptor/Descriptor.h"
#include <d3d12.h>

namespace
{
	D3D12_HEAP_PROPERTIES defProp{ 
		D3D12_HEAP_TYPE::D3D12_HEAP_TYPE_DEFAULT,
	    D3D12_CPU_PAGE_PROPERTY::D3D12_CPU_PAGE_PROPERTY_UNKNOWN,
	    D3D12_MEMORY_POOL::D3D12_MEMORY_POOL_UNKNOWN,
	    0,
	    0, 
	};
	D3D12_HEAP_PROPERTIES uplProp{
		D3D12_HEAP_TYPE::D3D12_HEAP_TYPE_UPLOAD,
		D3D12_CPU_PAGE_PROPERTY::D3D12_CPU_PAGE_PROPERTY_UNKNOWN,
		D3D12_MEMORY_POOL::D3D12_MEMORY_POOL_UNKNOWN,
		0,
		0 
	};
}

// コンストラクタ
Acceleration::Acceleration(std::weak_ptr<List>list, Acceleration* bottom) :
	list(list), tlasSize(0)
{
}

// デストラクタ
Acceleration::~Acceleration()
{
}

// リソース生成
void Acceleration::CreateRsc(const unsigned int& id, const size_t& size, const D3D12_HEAP_PROPERTIES& prop, const D3D12_RESOURCE_STATES& state, const D3D12_RESOURCE_FLAGS& flag)
{
	D3D12_RESOURCE_DESC desc{};
	desc.Alignment        = 0;
	desc.DepthOrArraySize = 1;
	desc.Dimension        = D3D12_RESOURCE_DIMENSION::D3D12_RESOURCE_DIMENSION_BUFFER;
	desc.Flags            = flag;
	desc.Format           = DXGI_FORMAT::DXGI_FORMAT_UNKNOWN;
	desc.Height           = 1;
	desc.Layout           = D3D12_TEXTURE_LAYOUT::D3D12_TEXTURE_LAYOUT_ROW_MAJOR;
	desc.MipLevels        = 1;
	desc.SampleDesc       = { 1, 0 };
	desc.Width            = size;

	okmonn::CreateRsc(&rsc[id], prop, desc, nullptr, state);
}

#include <DirectXMath.h>

// トップレベル構造生成
void Acceleration::CreateTop(Acceleration* bottom)
{
	D3D12_BUILD_RAYTRACING_ACCELERATION_STRUCTURE_INPUTS input{};
	input.DescsLayout = D3D12_ELEMENTS_LAYOUT::D3D12_ELEMENTS_LAYOUT_ARRAY;
	input.Flags       = D3D12_RAYTRACING_ACCELERATION_STRUCTURE_BUILD_FLAGS::D3D12_RAYTRACING_ACCELERATION_STRUCTURE_BUILD_FLAG_NONE;
	input.NumDescs    = 1;
	input.Type        = D3D12_RAYTRACING_ACCELERATION_STRUCTURE_TYPE::D3D12_RAYTRACING_ACCELERATION_STRUCTURE_TYPE_TOP_LEVEL;

	D3D12_RAYTRACING_ACCELERATION_STRUCTURE_PREBUILD_INFO info{};
	Device::Get().Dev()->GetRaytracingAccelerationStructurePrebuildInfo(&input, &info);

	CreateRsc(0, info.ScratchDataSizeInBytes, defProp, D3D12_RESOURCE_STATES::D3D12_RESOURCE_STATE_UNORDERED_ACCESS, D3D12_RESOURCE_FLAGS::D3D12_RESOURCE_FLAG_ALLOW_UNORDERED_ACCESS);
	CreateRsc(1, info.ResultDataMaxSizeInBytes, defProp, D3D12_RESOURCE_STATES::D3D12_RESOURCE_STATE_RAYTRACING_ACCELERATION_STRUCTURE, D3D12_RESOURCE_FLAGS::D3D12_RESOURCE_FLAG_ALLOW_UNORDERED_ACCESS);
	
	tlasSize = info.ResultDataMaxSizeInBytes;

	CreateRsc(2, sizeof(D3D12_RAYTRACING_INSTANCE_DESC), uplProp, D3D12_RESOURCE_STATES::D3D12_RESOURCE_STATE_GENERIC_READ, D3D12_RESOURCE_FLAGS::D3D12_RESOURCE_FLAG_NONE);

	D3D12_RAYTRACING_INSTANCE_DESC* instance = nullptr;
	okmonn::Map(rsc[2].Get(), (void**)&instance);
	instance->AccelerationStructure = bottom->Get()->GetGPUVirtualAddress();
	instance->Flags = D3D12_RAYTRACING_INSTANCE_FLAGS::D3D12_RAYTRACING_INSTANCE_FLAG_NONE;
	instance->InstanceContributionToHitGroupIndex = 0;
	instance->InstanceID = 0;
	instance->InstanceMask = 0xff;
	const float mat[3][4] = {
		{1,0,0,0},
		{0,1,0,0},
		{0,0,1,0},
	};
	memcpy(instance->Transform, &mat, sizeof(mat));
	okmonn::UnMap(rsc[2].Get());

	D3D12_BUILD_RAYTRACING_ACCELERATION_STRUCTURE_DESC desc{};
	desc.DestAccelerationStructureData    = rsc[1]->GetGPUVirtualAddress();
	desc.Inputs                           = input;
	desc.ScratchAccelerationStructureData = rsc[0]->GetGPUVirtualAddress();
	desc.SourceAccelerationStructureData  = rsc[2]->GetGPUVirtualAddress();
	list.lock()->Get()->BuildRaytracingAccelerationStructure(&desc, 0, nullptr);

	list.lock()->Barrier(rsc[1].Get());
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

	CreateRsc(0, info.ScratchDataSizeInBytes, defProp, D3D12_RESOURCE_STATES::D3D12_RESOURCE_STATE_UNORDERED_ACCESS, D3D12_RESOURCE_FLAGS::D3D12_RESOURCE_FLAG_ALLOW_UNORDERED_ACCESS);
	CreateRsc(1, info.ResultDataMaxSizeInBytes, defProp, D3D12_RESOURCE_STATES::D3D12_RESOURCE_STATE_RAYTRACING_ACCELERATION_STRUCTURE, D3D12_RESOURCE_FLAGS::D3D12_RESOURCE_FLAG_ALLOW_UNORDERED_ACCESS);

	D3D12_BUILD_RAYTRACING_ACCELERATION_STRUCTURE_DESC asDesc{};
	asDesc.DestAccelerationStructureData    = rsc[1]->GetGPUVirtualAddress();
	asDesc.Inputs                           = input;
	asDesc.ScratchAccelerationStructureData = rsc[0]->GetGPUVirtualAddress();
	list.lock()->Get()->BuildRaytracingAccelerationStructure(&asDesc, 0, nullptr);

	list.lock()->Barrier(rsc[1].Get());
}

// リソース取得
ID3D12Resource* Acceleration::Get(void) const
{
	return rsc[1].Get();
}
