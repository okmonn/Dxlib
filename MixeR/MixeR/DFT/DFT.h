#pragma once
#include <vector>
#include <memory>

class MyLib;
class Compute;
class Sound;
class Primitive;

// GPUで離散フーリエ変換
class DFT
{
public:
	// コンストラクタ
	DFT(std::weak_ptr<MyLib>lib, std::weak_ptr<Sound>sound);
	// デストラクタ
	~DFT();

	// 処理
	void Run(void);

private:
	// 初期化
	void Init(void);


	// ライブラリ
	std::unique_ptr<MyLib>lib;

	// サウンド
	std::weak_ptr<Sound>sound;

	// コンピュート
	std::unique_ptr<Compute>compute;

	// プリミティブ
	std::unique_ptr< Primitive>prim;

	// 実数
	std::vector<float>real;

	// 虚数
	std::vector<float>imag;
};
