#include "TexLoader.h"
#include "WICTextureLoader12.h"
#include "../etc/Func.h"
#include "../etc/Release.h"

// �R���X�g���N�^
TexLoader::TexLoader()
{
}

// �f�X�g���N�^
TexLoader::~TexLoader()
{
	for (auto& i : rsc)
	{
		Release(i.second);
	}
	for (auto& i : decode)
	{
		i.second.release();
	}
}

// �ǂݍ���
long TexLoader::Load(const std::string & fileName)
{
	if (rsc.find(fileName) != rsc.end())
	{
		return S_OK;
	}

	sub[fileName] = std::make_shared<D3D12_SUBRESOURCE_DATA>();
	auto hr = DirectX::LoadWICTextureFromFile(Dev, func::ChangeCode(fileName).c_str(), &rsc[fileName], decode[fileName], *sub[fileName]);
	if (FAILED(hr))
	{
		func::DebugLog("�摜�ǂݍ��݁F���s");
	}

	return hr;
}

// �f�[�^�폜
void TexLoader::Delete(const std::string & fileName)
{
	if (rsc.find(fileName) != rsc.end())
	{
		rsc.erase(rsc.find(fileName));
		decode.erase(decode.find(fileName));
		sub.erase(sub.find(fileName));
	}
}

// �C���X�^���X�ϐ��擾
TexLoader & TexLoader::Get(void)
{
	static TexLoader instance;
	return instance;
}

// ���\�[�X�擾
ID3D12Resource * TexLoader::GetRsc(const std::string & fileName)
{
	if (rsc.find(fileName) == rsc.end())
	{
		return nullptr;
	}

	return rsc[fileName];
}

// �f�R�[�h�擾
uchar * TexLoader::GetDecode(const std::string & fileName)
{
	if (decode.find(fileName) == decode.end())
	{
		return nullptr;
	}

	return decode[fileName].get();
}

// �T�u�f�[�^�擾
std::shared_ptr<D3D12_SUBRESOURCE_DATA> TexLoader::GetSub(const std::string & fileName)
{
	if (sub.find(fileName) == sub.end())
	{
		return nullptr;
	}
	
	return sub[fileName];
}

// �摜�T�C�Y�擾
Vec2f TexLoader::GetSize(const std::string & fileName)
{
	if (rsc.find(fileName) == rsc.end())
	{
		return Vec2f();
	}

	return Vec2f(float(rsc[fileName]->GetDesc().Width), float(rsc[fileName]->GetDesc().Height));
}
