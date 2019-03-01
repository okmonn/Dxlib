#include <d3dcompiler.h>
#include "Root.h"
#include "../etc/Func.h"
#include "../etc/Release.h"
#include <iostream>

// �R���X�g���N�^
Root::Root() : 
	root(nullptr), sig(nullptr), vertex(nullptr), geometry(nullptr), pixel(nullptr), compute(nullptr)
{
	vBlob = {};
	gBlob = {};
	pBlob = {};
	cBlob = {};
}

// �f�X�g���N�^
Root::~Root()
{
	Release(compute);
	Release(pixel);
	Release(geometry);
	Release(vertex);
	Release(sig);
	Release(root);
}

// ���_�V�F�[�_�R���p�C��
void Root::Vertex(const std::string& fileName, const std::string& func, const std::string& ver)
{
	if (fileName.find(".hlsl") != std::string::npos)
	{
		Compile(fileName, func, ver, &vertex);
		RootInfo(vertex);
	}
	else if (fileName.find(".cso") != std::string::npos)
	{
		vBlob = std::make_shared<Blob>();
		Load(fileName, vBlob);
		RootInfo(vBlob);
	}
	else
	{

	}
	
	CreateRoot();
}

// �W�I���g���[�V�F�[�_�R���p�C��
void Root::Geometry(const std::string & fileName, const std::string & func, const std::string & ver)
{
	if (fileName.find(".hlsl") != std::string::npos)
	{
		Compile(fileName, func, ver, &geometry);
	}
	else if (fileName.find(".cso") != std::string::npos)
	{
		gBlob = std::make_shared<Blob>();
		Load(fileName, gBlob);
	}
	else
	{

	}
}

// �s�N�Z���V�F�[�_�R���p�C��
void Root::Pixel(const std::string & fileName, const std::string & func, const std::string & ver)
{
	if (fileName.find(".hlsl") != std::string::npos)
	{
		Compile(fileName, func, ver, &pixel);
	}
	else if (fileName.find(".cso") != std::string::npos)
	{
		pBlob = std::make_shared<Blob>();
		Load(fileName, pBlob);
	}
	else
	{

	}
}

// �R���s���[�g�V�F�[�_�R���p�C��
void Root::Compute(const std::string & fileName, const std::string & func, const std::string & ver)
{
	if (fileName.find(".hlsl") != std::string::npos)
	{
		Compile(fileName, func, ver, &compute);
		RootInfo(compute);
	}
	else if (fileName.find(".cso") != std::string::npos)
	{
		cBlob = std::make_shared<Blob>();
		Load(fileName, cBlob);
		RootInfo(cBlob);
	}
	else
	{
		
	}
	
	CreateRoot();
}

// �V�F�[�_�R���p�C��
long Root::Compile(const std::string& fileName, const std::string& func, const std::string& ver, ID3DBlob** blob)
{
	auto pass = func::ChangeCode(fileName);
	auto hr = D3DCompileFromFile(pass.c_str(), nullptr, D3D_COMPILE_STANDARD_FILE_INCLUDE, func.c_str(), ver.c_str(),
		D3DCOMPILE_DEBUG | D3DCOMPILE_SKIP_OPTIMIZATION, 0, *(&blob), nullptr);
	if (FAILED(hr))
	{
		func::DebugLog("�V�F�[�_�R���p�C���F���s");
	}

	return hr;
}

// .cso�ǂݍ���
int Root::Load(const std::string& fileName, std::shared_ptr<Blob> blob)
{
	FILE* file = nullptr;
	if (fopen_s(&file, fileName.c_str(), "rb") != 0)
	{
		func::DebugLog(".cso�ǂݍ��݁F���s");
		return -1;
	}

	//�I�[�Ɉړ�
	fseek(file, 0, SEEK_END);
	//�T�C�Y�擾
	blob->data.resize(ftell(file));
	blob->size = blob->data.size();
	//�擪�Ɉړ�
	fseek(file, 0, SEEK_SET);
	fread(blob->data.data(), sizeof(blob->data[0]) * blob->data.size(), 1, file);

	fclose(file);

	return 0;
}

// ���[�g���擾
long Root::RootInfo(ID3DBlob* blob)
{
	auto hr = D3DGetBlobPart(blob->GetBufferPointer(), blob->GetBufferSize(), D3D_BLOB_PART::D3D_BLOB_ROOT_SIGNATURE, 0, &sig);
	if (FAILED(hr))
	{
		func::DebugLog("���[�g�V�O�l�`�����擾�F���s");
	}

	return hr;
}

// ���[�g���擾
long Root::RootInfo(std::shared_ptr<Blob> blob)
{
	auto hr = D3DGetBlobPart(blob->data.data(), blob->size, D3D_BLOB_PART::D3D_BLOB_ROOT_SIGNATURE, 0, &sig);
	if (FAILED(hr))
	{
		func::DebugLog("���[�g�V�O�l�`�����擾�F���s");
	}

	return hr;
}

// ���[�g�V�O�l�`������
long Root::CreateRoot(void)
{
	auto hr = Dev->CreateRootSignature(0, sig->GetBufferPointer(), sig->GetBufferSize(), IID_PPV_ARGS(&root));
	if (FAILED(hr))
	{
		func::DebugLog("���[�g�V�O�l�`�������F���s");
	}

	return hr;
}

// ���[�g�V�O�l�`���擾
ID3D12RootSignature* Root::Get(void) const
{
	return root;
}

// �V�O�l�`���擾
ID3DBlob* Root::GetSig(void) const
{
	return sig;
}

// ���_�V�F�[�_�擾
std::tuple<ID3DBlob*, std::shared_ptr<Blob>> Root::GetVertex(void) const
{
	return std::forward_as_tuple(vertex, vBlob);
}

// �W�I���g���[�V�F�[�_�擾
std::tuple<ID3DBlob*, std::shared_ptr<Blob>> Root::GetGeometry(void) const
{
	return std::forward_as_tuple(geometry, gBlob);
}

// �s�N�Z���V�F�[�_�擾
std::tuple<ID3DBlob*, std::shared_ptr<Blob>> Root::GetPixel(void) const
{
	return std::forward_as_tuple(pixel, pBlob);
}

// �R���s���[�g�V�F�[�_�擾
std::tuple<ID3DBlob*, std::shared_ptr<Blob>> Root::GetCompute(void) const
{
	return std::forward_as_tuple(compute, cBlob);
}
