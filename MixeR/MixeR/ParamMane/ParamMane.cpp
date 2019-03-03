#include "ParamMane.h"
#include "../Mouse/Mouse.h"
#include "../Thumb/Thumb.h"
#include <MyLib.h>

// �R���X�g���N�^
ParamMane::ParamMane(std::weak_ptr<MyLib> lib, std::weak_ptr<Sound> sound, std::weak_ptr<Mouse> mouse) : 
	lib(lib), sound(sound), mouse(mouse), old(-1.0f)
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
	SetParam("thd",   0.01f, 1.0f,   1.0f, Vec2f(100.0f * index++, 0.0f));
	SetParam("ratio", 0.0f,  1.0f,   1.0f, Vec2f(100.0f * index++, 0.0f));
	SetParam("dis",   1.0f,  10.0f,  1.0f, Vec2f(100.0f * index++, 0.0f));
	SetParam("depth", 0.0f,  1.0f,   0.0f, Vec2f(100.0f * index++, 0.0f));
	SetParam("rate",  0.0f,  10.0f,  0.0f, Vec2f(100.0f * index++, 0.0f));
	SetParam("pan",   0.0f,  180.0f, 90.0, Vec2f(100.0f * index++, 0.0f));
	SetParam("vol",   0.0f,  10.0f,  1.0f, Vec2f(100.0f * index++, 0.0f));
	SetParam("decay", 0.01f, 1.0f, 1.0f, Vec2f(100.0f * index++, 0.0f));
}

//�֐��|�C���^�Z�b�g
void ParamMane::SetFunc(const std::string & name, float & effect)
{
	if (func.find(name) != func.end())
	{
		return;
	}

	func[name] = [&](Thumb& i)->void {
		i.UpData();
		effect = i.GetEffect();
	};
}

// �֐��|�C���^�Z�b�g
void ParamMane::InitFunc(void)
{
	//臒l����
	SetFunc("thd", sound.lock()->comp.threshold);
	//���k�䗦����
	SetFunc("ratio", sound.lock()->comp.ratio);
	//�f�B�X�g�[�V����
	SetFunc("dis", sound.lock()->distortion);
	//�ϒ��[�x����
	SetFunc("depth", sound.lock()->toremor.depth);
	//�ϒ����g������
	SetFunc("rate", sound.lock()->toremor.rate);
	//��ʒ���
	SetFunc("pan", sound.lock()->pan);
	//���ʒ���
	SetFunc("vol", sound.lock()->volume);
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
}
