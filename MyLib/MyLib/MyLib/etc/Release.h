#pragma once
#include "../Device/Device.h"
#include <d3d12.h>
#include <tchar.h>
#include <dxgi1_6.h>

#define Dev Device::Get().GetDev()
#define Factory Device::Get().GetFactory()

#define Release(X) { if((X) != nullptr) (X)->Release(); }
