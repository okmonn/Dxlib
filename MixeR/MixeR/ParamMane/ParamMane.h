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

enum class Type {
	low,
	band,
	high
};

// �p�����[�^�Ǘ�S
class ParamMane
{
public:
	// �R���X�g���N�^
	ParamMane(std::weak_ptr<MyLib>lib, std::weak_ptr<Sound>sound, std::weak_ptr<Mouse>mouse);
	// �f�X�g���N�^
	~ParamMane();

	// �`��
	void Draw(void);

	// ����
	void UpData(void);

private:
	// �p�����[�^�Z�b�g
	void SetParam(const std::string& name, const float& min, const float& max, const float& now, const Vec2f& pos, const Vec2f& size = 100.0f);

	// ������
	void Init(void);

	//�֐��|�C���^�Z�b�g
	template <typename T>
	void SetFunc(const std::string& name, T& effect);

	// �֐��|�C���^������
	void InitFunc(void);


	// ���C�u����
	std::weak_ptr<MyLib>lib;

	// �T�E���h
	std::weak_ptr<Sound>sound;

	// �}�E�X
	std::weak_ptr<Mouse>mouse;

	// �O�̒l
	float old;

	// �t�B���^�^�C�v
	Type type;

	// �p�����[�^
	std::unordered_map<std::string, std::shared_ptr<Thumb>>thumb;
	
	// �֐��|�C���^
	std::unordered_map<std::string, std::function<void(Thumb& i)>>func;
	std::unordered_map<Type, std::function<void(void)>>filter;
};
