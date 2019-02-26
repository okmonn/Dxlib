#pragma once
#include "../etc/Define.h"
#include <string>
#include <memory>
#include <unordered_map>

// �e�N�X�`�����[�_�[
class TexLoader
{
public:
	// �f�X�g���N�^
	~TexLoader();

	// �ǂݍ���
	long Load(const std::string& fileName);

	// �f�[�^�폜
	void Delete(const std::string& fileName);

	// �C���X�^���X�ϐ��擾
	static TexLoader& Get(void);
	// ���\�[�X�擾
	ID3D12Resource* GetRsc(const std::string& fileName);
	// �f�R�[�h�擾
	uchar* GetDecode(const std::string& fileName);
	// �T�u�f�[�^�擾
	D3D12_SUBRESOURCE_DATA GetSub(const std::string& fileName);
	// �摜�T�C�Y�擾
	Vec2f GetSize(const std::string& fileName);

private:
	TexLoader();
	TexLoader(const TexLoader&) = delete;
	void operator=(const TexLoader&) = delete;


	// ���\�[�X
	std::unordered_map<std::string, ID3D12Resource*>rsc;

	// �f�R�[�h
	std::unordered_map<std::string, std::unique_ptr<uchar[]>>decode;

	// �T�u�f�[�^
	std::unordered_map<std::string, D3D12_SUBRESOURCE_DATA>sub;
};
