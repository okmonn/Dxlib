#include "Device.h"
#include <d3d12.h>
#include <crtdbg.h>
#include <dxgi1_6.h>

// �@�\���x���ꗗ
const D3D_FEATURE_LEVEL level[] = {
	D3D_FEATURE_LEVEL::D3D_FEATURE_LEVEL_12_1,
	D3D_FEATURE_LEVEL::D3D_FEATURE_LEVEL_12_0,
	D3D_FEATURE_LEVEL::D3D_FEATURE_LEVEL_11_1,
	D3D_FEATURE_LEVEL::D3D_FEATURE_LEVEL_11_0
};

// �R���X�g���N�^
Device::Device() : 
	dev(nullptr)
{
	CreateDev();
}

// �f�X�g���N�^
Device::~Device()
{
}

// �f�o�C�X����
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

	//�ŏI�I�ȃA�_�v�^�[���Z�b�g����
	hr = factory->EnumAdapters1(index, &adap);
	
	for (const D3D_FEATURE_LEVEL& i : level)
	{
		hr = D3D12CreateDevice(adap.Get(), i, IID_PPV_ARGS(&dev));
		if (hr == S_OK)
		{
			break;
		}
	}
	_ASSERT(hr == S_OK);
}

// �f�o�C�X�擾
ID3D12Device* Device::Dev(void) const
{
	return dev.Get();
}
