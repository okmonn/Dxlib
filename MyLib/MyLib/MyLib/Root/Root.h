#pragma once
#include "../etc/Define.h"
#include <tuple>
#include <string>
#include <vector>
#include <memory>

// �V�F�[�_���
struct Blob {
	//�f�[�^
	std::vector<uchar>data;
	//�T�C�Y
	size_t size;
};

// ���[�g�V�O�l�`��
class Root
{
public:
	// �R���X�g���N�^
	Root();
	// �f�X�g���N�^
	~Root();

	// ���_�V�F�[�_�R���p�C��
	void Vertex(const std::string& fileName, const std::string& func = "VS", const std::string& ver = "vs_5_1");
	// �W�I���g���[�V�F�[�_�R���p�C��
	void Geometry(const std::string& fileName, const std::string& func = "GS", const std::string& ver = "gs_5_1");
	// �s�N�Z���V�F�[�_�R���p�C��
	void Pixel(const std::string& fileName, const std::string& func = "PS", const std::string& ver = "ps_5_1");
	// �R���s���[�g�V�F�[�_�R���p�C��
	void Compute(const std::string& fileName, const std::string& func = "CS", const std::string& ver = "cs_5_1");

	// ���[�g�V�O�l�`���擾
	ID3D12RootSignature* Get(void) const;
	// �V�O�l�`���擾
	ID3DBlob* GetSig(void) const;
	// ���_�V�F�[�_�擾
	std::tuple<ID3DBlob*, std::shared_ptr<Blob>> GetVertex(void) const;
	// �W�I���g���[�V�F�[�_�擾
	std::tuple<ID3DBlob*, std::shared_ptr<Blob>> GetGeometry(void) const;
	// �s�N�Z���V�F�[�_�擾
	std::tuple<ID3DBlob*, std::shared_ptr<Blob>> GetPixel(void) const;
	// �R���s���[�g�V�F�[�_�擾
	std::tuple<ID3DBlob*, std::shared_ptr<Blob>> GetCompute(void) const;

private:
	Root(const Root&) = delete;
	void operator=(const Root&) = delete;

	// �V�F�[�_�R���p�C��
	long Compile(const std::string& fileName, const std::string& func, const std::string& ver, ID3DBlob** blob);

	// .cso�ǂݍ���
	int Load(const std::string& fileName, std::shared_ptr<Blob>blob);

	// ���[�g���擾
	long RootInfo(ID3DBlob* blob);
	long RootInfo(std::shared_ptr<Blob> blob);

	// ���[�g�V�O�l�`������
	long CreateRoot(void);


	// ���[�g
	ID3D12RootSignature* root;

	// �V�O�l�`��
	ID3DBlob* sig;

	// ���_�V�F�[�_
	ID3DBlob* vertex;
	std::shared_ptr<Blob>vBlob;

	// �W�I���g���[�V�F�[�_�[
	ID3DBlob* geometry;
	std::shared_ptr<Blob>gBlob;

	// �s�N�Z���V�F�[�_
	ID3DBlob* pixel;
	std::shared_ptr<Blob>pBlob;

	// �R���s���[�g�V�F�[�_
	ID3DBlob* compute;
	std::shared_ptr<Blob>cBlob;
};
