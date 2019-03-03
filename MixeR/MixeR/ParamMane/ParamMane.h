#pragma once
#include <Math/Vector2.h>
#include <string>
#include <memory>
#include <functional>
#include <unordered_map>

class MyLib;
class Sound;
class Mouse;
class Thumb;

// パラメータ管理S
class ParamMane
{
public:
	// コンストラクタ
	ParamMane(std::weak_ptr<MyLib>lib, std::weak_ptr<Sound>sound, std::weak_ptr<Mouse>mouse);
	// デストラクタ
	~ParamMane();

	// 描画
	void Draw(void);

	// 処理
	void UpData(void);

private:
	// パラメータセット
	void SetParam(const std::string& name, const float& min, const float& max, const float& now, const Vec2f& pos, const Vec2f& size = 100.0f);

	// 初期化
	void Init(void);

	//関数ポインタセット
	void SetFunc(const std::string& name, float& effect);

	// 関数ポインタ初期化
	void InitFunc(void);


	// ライブラリ
	std::weak_ptr<MyLib>lib;

	// サウンド
	std::weak_ptr<Sound>sound;

	// マウス
	std::weak_ptr<Mouse>mouse;

	// 前の値
	float old;

	// パラメータ
	std::unordered_map<std::string, std::unique_ptr<Thumb>>thumb;
	
	// 関数ポインタ
	std::unordered_map<std::string, std::function<void(Thumb& i)>>func;
};
