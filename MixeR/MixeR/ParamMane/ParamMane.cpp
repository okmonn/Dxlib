#include "ParamMane.h"
#include "../Mouse/Mouse.h"
#include "../Thumb/Thumb.h"
#include <MyLib.h>

// �R���X�g���N�^
ParamMane::ParamMane(std::weak_ptr<MyLib> lib, std::weak_ptr<Sound> sound, std::weak_ptr<Mouse> mouse) : 
	lib(lib), sound(sound), mouse(mouse), old(-1.0f), type(Type::low)
{
	Init();
	InitFunc();
}

// �f�X�g���N�^
ParamMane::~ParamMane()
{
}

// �p�����[�^�Z�b�g
void ParamMane::SetParam(const std::string& name, const float& min, const float& max, const float& now, const Vec2f& pos, const Vec2f& size)
{
	if (thumb.find(name) != thumb.end())
	{
		return;
	}

	thumb[name] = std::make_unique<Thumb>(pos, size, min, max, now);
}

// ������
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

//�֐��|�C���^�Z�b�g
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

// �֐��|�C���^�Z�b�g
void ParamMane::InitFunc(void)
{
	//臒l����
	SetFunc("thd",   sound.lock()->comp.threshold);
	//���k�䗦����
	SetFunc("ratio", sound.lock()->comp.ratio);
	//�f�B�X�g�[�V����
	SetFunc("dis",   sound.lock()->distortion);
	//�ϒ��[�x����
	SetFunc("depth", sound.lock()->toremor.depth);
	//�ϒ����g������
	SetFunc("rate",  sound.lock()->toremor.rate);
	//��ʒ���
	SetFunc("pan",   sound.lock()->pan);
	//���ʒ���
	SetFunc("vol",   sound.lock()->volume);
	//�x�����ʒ���
	SetFunc("decay", sound.lock()->delayParam.decay);
	//�x�����Ԓ���
	SetFunc("time",  sound.lock()->delayParam.time);
	//�x���񐔒���
	SetFunc("loop",  sound.lock()->delayParam.loop);
	//�J�b�g�I�t���g������
	SetFunc("cutoff", sound.lock()->filterParam.cutoff);
	//�N�I���e�B�t�@�N�^����
	SetFunc("bw", sound.lock()->filterParam.bw);

	//���[�p�X
	filter[Type::low] = [&]()->void {
		sound.lock()->LowPass();
	};
	//�o���h�p�X
	filter[Type::band] = [&]()->void {
		sound.lock()->BandPass();
	};
	//�n�C�p�X
	filter[Type::high] = [&]()->void {
		sound.lock()->HighPass();
	};
}

// �`��
void ParamMane::Draw(void)
{
	for (auto& i : thumb)
	{
		lib.lock()->Draw(*(i.second->tex));
	}
}

// ����
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
