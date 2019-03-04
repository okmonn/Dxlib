#include "ParamMane.h"
#include "../Mouse/Mouse.h"
#include "../Thumb/Thumb.h"
#include <MyLib.h>

// コンストラクタ
ParamMane::ParamMane(std::weak_ptr<MyLib> lib, std::weak_ptr<Sound> sound, std::weak_ptr<Mouse> mouse) : 
	lib(lib), sound(sound), mouse(mouse), old(-1.0f), type(Type::low)
{
	Init();
	InitFunc();
}

// デストラクタ
ParamMane::~ParamMane()
{
}

// パラメータセット
void ParamMane::SetParam(const std::string& name, const float& min, const float& max, const float& now, const Vec2f& pos, const Vec2f& size)
{
	if (thumb.find(name) != thumb.end())
	{
		return;
	}

	thumb[name] = std::make_unique<Thumb>(pos, size, min, max, now);
}

// 初期化
void ParamMane::Init(void)
{
	uint index = 0;
	SetParam("thd",   0.1f,  1.0f,   1.0f, Vec2f(100.0f * (index % 5), 100.0f * (index / 5)));
	++index;
	SetParam("ratio", 0.0f,  1.0f,   1.0f, Vec2f(100.0f * (index % 5), 100.0f * (index / 5)));
	++index;
	SetParam("dis",   1.0f,  10.0f,  1.0f, Vec2f(100.0f * (index % 5), 100.0f * (index / 5)));
	++index;
	SetParam("depth", 0.0f,  1.0f,   0.0f, Vec2f(100.0f * (index % 5), 100.0f * (index / 5)));
	++index;
	SetParam("rate",  0.0f,  10.0f,  0.0f, Vec2f(100.0f * (index % 5), 100.0f * (index / 5)));
	++index;
	SetParam("pan",   0.0f,  180.0f, 90.0, Vec2f(100.0f * (index % 5), 100.0f * (index / 5)));
	++index;
	SetParam("vol",   0.0f,  10.0f,  1.0f, Vec2f(100.0f * (index % 5), 100.0f * (index / 5)));
	++index;
	SetParam("decay", 0.01f, 1.0f,   1.0f, Vec2f(100.0f * (index % 5), 100.0f * (index / 5)));
	++index;
	SetParam("time",  0.0f,  1.0f,   0.0f, Vec2f(100.0f * (index % 5), 100.0f * (index / 5)));
	++index;
	SetParam("loop",  1.0f,  10.0f,  1.0f, Vec2f(100.0f * (index % 5), 100.0f * (index / 5)));
	++index;
	SetParam("cutoff", 10.0f, func::Floor(float(sound.lock()->info.sample / 2), 3), func::Floor(float(sound.lock()->info.sample / 2), 3), Vec2f(100.0f * (index % 5), 100.0f * (index / 5)));
	++index;
	SetParam("bw", 0.01f, 5.0f, 1.0f / std::sqrt(2.0f), Vec2f(100.0f * (index % 5), 100.0f * (index / 5)));
	++index;
}

//関数ポインタセット
template <typename T>
void ParamMane::SetFunc(const std::string& name, T& effect)
{
	if (func.find(name) != func.end())
	{
		return;
	}

	effect = T(thumb[name]->GetEffect());
	func[name] = [&](Thumb& i)->void {
		i.UpData();
		effect = T(i.GetEffect());
	};
}
template void ParamMane::SetFunc<float>(const std::string&, float&);
template void ParamMane::SetFunc<uint>(const std::string&, uint&);

// 関数ポインタセット
void ParamMane::InitFunc(void)
{
	//閾値調節
	SetFunc("thd",   sound.lock()->comp.threshold);
	//圧縮比率調節
	SetFunc("ratio", sound.lock()->comp.ratio);
	//ディストーション
	SetFunc("dis",   sound.lock()->distortion);
	//変調深度調節
	SetFunc("depth", sound.lock()->toremor.depth);
	//変調周波数調節
	SetFunc("rate",  sound.lock()->toremor.rate);
	//定位調節
	SetFunc("pan",   sound.lock()->pan);
	//音量調節
	SetFunc("vol",   sound.lock()->volume);
	//遅延音量調節
	SetFunc("decay", sound.lock()->delayParam.decay);
	//遅延時間調節
	SetFunc("time",  sound.lock()->delayParam.time);
	//遅延回数調節
	SetFunc("loop",  sound.lock()->delayParam.loop);
	//カットオフ周波数調節
	SetFunc("cutoff", sound.lock()->filterParam.cutoff);
	//クオリティファクタ調節
	SetFunc("bw", sound.lock()->filterParam.bw);

	//ローパス
	filter[Type::low] = [&]()->void {
		sound.lock()->LowPass();
	};
	//バンドパス
	filter[Type::band] = [&]()->void {
		sound.lock()->BandPass();
	};
	//ハイパス
	filter[Type::high] = [&]()->void {
		sound.lock()->HighPass();
	};
}

// 描画
void ParamMane::Draw(void)
{
	for (auto& i : thumb)
	{
		lib.lock()->Draw(*(i.second->tex));
	}
}

// 処理
void ParamMane::UpData(void)
{
	if (KEY.Trigger(KeyCode::Return))
	{
		type = uint(type) + 1 > uint(Type::high) ? Type(0) : Type(uint(type) + 1);
		filter[type]();
	}

	if (mouse.lock()->GetClick() < 0.0f)
	{
		old = -1.0f;
		return;
	}

	const int offset = 10;
	auto m = mouse.lock()->GetClick();
	for (auto& i : thumb)
	{
		if (i.second->pos.x < m.x && m.x < i.second->pos.x + i.second->size.x
			&& i.second->pos.y < m.y && m.y < i.second->pos.y + i.second->size.y)
		{
			if (old < 0.0f)
			{
				old = i.second->effect;
			}
			float tmp = (m.y - mouse.lock()->GetPos().y) / offset * 0.01f;
			i.second->effect = old + i.second->max * tmp;
			func[i.first](*i.second);
			break;
		}
	}

	filter[type]();
}
