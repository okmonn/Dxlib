#pragma once
#include "../etc/Define.h"
#include <string>
#include <vector>

// ���[�g�V�O�l�`��
class Root
{
public:
	// �R���X�g���N�^
	Root();
	// �f�X�g���N�^
	~Root();

	// ���_�V�F�[�_�R���p�C��
	void Vertex(const std::string& fileName, const std::string& func, const std::string& ver);
	// �W�I���g���[�V�F�[�_�R���p�C��
	void Geometry(const std::string& fileName, const std::string& func, const std::string& ver);
	// �s�N�Z���V�F�[�_�R���p�C��
	void Pixel(const std::string& fileName, const std::string& func, const std::string& ver);
	// �R���s���[�g�V�F�[�_�R���p�C��
	void Compute(const std::string& fileName, const std::string& func, const std::string& ver);

	// .cso�ǂݍ���
	void Vertex(const std::string& fileName);
	void Geometry(const std::string& fileName);
	void Pixel(const std::string& fileName);
	void Compute(const std::string& fileName);

	// ���\�[�X�ǂݍ���
	void Vertex(const int& id);
	void Geometry(const int& id);
	void Pixel(const int& id);
	void Compute(const int& id);

	// ���[�g�V�O�l�`���擾
	ID3D12RootSignature* Get(void) const;
	// �V�O�l�`���擾
	ID3DBlob* GetSig(void) const;
	// ���_�V�F�[�_�擾
	ID3DBlob* GetVertex(void) const;
	// �W�I���g���[�V�F�[�_�擾
	ID3DBlob* GetGeometry(void) const;
	// �s�N�Z���V�F�[�_�擾
	ID3DBlob* GetPixel(void) const;
	// �R���s���[�g�V�F�[�_�擾
	ID3DBlob* GetCompute(void) const;

private:
	Root(const Root&) = delete;
	void operator=(const Root&) = delete;

	// �V�F�[�_�R���p�C��
	long Compile(const std::string& fileName, const std::string& func, const std::string& ver, ID3DBlob** blob);

	// .cso�ǂݍ���
	long Load(const std::string& fileName, ID3DBlob** blob);

	// ���\�[�X�ǂݍ���
	long Read(const int& id, ID3DBlob** blob);

	// ���[�g���擾
	long RootInfo(ID3DBlob* blob);

	// ���[�g�V�O�l�`������
	long CreateRoot(void);


	// ���[�g
	ID3D12RootSignature* root;

	// �V�O�l�`��
	ID3DBlob* sig;

	// ���_�V�F�[�_
	ID3DBlob* vertex;

	// �W�I���g���[�V�F�[�_�[
	ID3DBlob* geometry;

	// �s�N�Z���V�F�[�_
	ID3DBlob* pixel;

	// �R���s���[�g�V�F�[�_
	ID3DBlob* compute;
};
