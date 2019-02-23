#pragma once
#include "../etc/Define.h"

class Device
{
public:
	// デストラクタ
	~Device();

	// インスタンス変数取得
	static Device& Get(void);

	// デバイス取得
	ID3D12Device* GetDev(void) const;
	// ファクトリー取得
	IDXGIFactory4* GetFactory(void) const;

private:
	// コンストラクタ
	Device();
	Device(const Device&) = delete;
	void operator=(const Device&) = delete;

	// ファクトリー生成
	long CreateFactory(void);

	// デバイス生成
	long CreateDev(void);

	// 初期化
	void Init(void);


	// デバイス
	ID3D12Device* dev;

	// ファクトリー
	IDXGIFactory4* factory;
};
