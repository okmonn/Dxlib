#include <d3dcompiler.h>
#include "Root.h"
#include "../etc/Func.h"
#include "../etc/Release.h"

// �R���X�g���N�^
Root::Root() : 
	root(nullptr), sig(nullptr), vertex(nullptr), geometry(nullptr), pixel(nullptr), compute(nullptr)
{
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
	}
	else if (fileName.find(".cso") != std::string::npos)
	{
		Load(fileName, &vertex);
	}
	else
	{

	}
	
	RootInfo(vertex);
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
		Load(fileName, &geometry);
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
		Load(fileName, &pixel);
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
	}
	else if (fileName.find(".cso") != std::string::npos)
	{
		Load(fileName, &compute);
	}
	else
	{
		
	}
	
	RootInfo(compute);
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
long Root::Load(const std::string& fileName, ID3DBlob** blob)
{
	auto pass = func::ChangeCode(fileName);
	auto hr = D3DReadFileToBlob(pass.c_str(), blob);
	if (FAILED(hr))
	{
		func::DebugLog(".cso�ǂݍ��݁F���s");
	}

	return hr;
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
ID3DBlob* Root::GetVertex(void) const
{
	return vertex;
}

// �W�I���g���[�V�F�[�_�擾
ID3DBlob* Root::GetGeometry(void) const
{
	return geometry;
}

// �s�N�Z���V�F�[�_�擾
ID3DBlob* Root::GetPixel(void) const
{
	return pixel;
}

// �R���s���[�g�V�F�[�_�擾
ID3DBlob* Root::GetCompute(void) const
{
	return compute;
}
