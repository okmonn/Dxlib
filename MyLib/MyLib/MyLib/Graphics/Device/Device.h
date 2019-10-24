#pragma once
#include "../../etc/Single.h"
#include <wrl.h>

struct ID3D12Device5;
struct IDXGIFactory1;

class Device :
	public Single<Device>
{
	friend Single<Device>;
public:
	// デバイス取得
	ID3D12Device5* Dev(void) const;

private:
	// コンストラクタ
	Device();
	// デストラクタ
	~Device();

	// デバイス生成
	void CreateDev(void);


	// デバイス
	Microsoft::WRL::ComPtr<ID3D12Device5>dev;
};
