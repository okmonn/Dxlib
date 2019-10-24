#include "Device.h"
#include <d3d12.h>
#include <crtdbg.h>
#include <dxgi1_6.h>

// 機能レベル一覧
const D3D_FEATURE_LEVEL level[] = {
	D3D_FEATURE_LEVEL::D3D_FEATURE_LEVEL_12_1,
	D3D_FEATURE_LEVEL::D3D_FEATURE_LEVEL_12_0,
	D3D_FEATURE_LEVEL::D3D_FEATURE_LEVEL_11_1,
	D3D_FEATURE_LEVEL::D3D_FEATURE_LEVEL_11_0
};

// コンストラクタ
Device::Device() : 
	dev(nullptr)
{
	CreateDev();
}

// デストラクタ
Device::~Device()
{
}

// デバイス生成
void Device::CreateDev(void)
{
	Microsoft::WRL::ComPtr<IDXGIFactory7>factory = nullptr;
	auto hr = CreateDXGIFactory(IID_PPV_ARGS(&factory));
	_ASSERT(hr == S_OK);

	Microsoft::WRL::ComPtr<IDXGIAdapter1>adap = nullptr;
	unsigned int revision = 0;
	unsigned int index    = 0;
	for (unsigned int i = 0; factory->EnumAdapters1(i, &adap) != DXGI_ERROR_NOT_FOUND; ++i)
	{
		DXGI_ADAPTER_DESC1 desc{};
		hr = adap->GetDesc1(&desc);
		_ASSERT(hr == S_OK);

		if (desc.Flags & DXGI_ADAPTER_FLAG::DXGI_ADAPTER_FLAG_SOFTWARE)
		{
			continue;
		}

		if (revision < desc.Revision)
		{
			revision = desc.Revision;
			index = i;
		}
	}

	//最終的なアダプターをセットする
	hr = factory->EnumAdapters1(index, &adap);
	
	for (const D3D_FEATURE_LEVEL& i : level)
	{
		if (SUCCEEDED(D3D12CreateDevice(adap.Get(), i, IID_PPV_ARGS(&dev))))
		{
			break;
		}
	}
	_ASSERT(hr == S_OK);

	D3D12_FEATURE_DATA_D3D12_OPTIONS5 option{};
	hr = dev->CheckFeatureSupport(D3D12_FEATURE::D3D12_FEATURE_D3D12_OPTIONS5, &option, sizeof(option));
	_ASSERT(hr == S_OK);
	if (option.RaytracingTier == D3D12_RAYTRACING_TIER_NOT_SUPPORTED)
	{
		OutputDebugStringA("\nDirectX Raytracing is not supported\n");
	}
}

// デバイス取得
ID3D12Device5* Device::Dev(void) const
{
	return dev.Get();
}
