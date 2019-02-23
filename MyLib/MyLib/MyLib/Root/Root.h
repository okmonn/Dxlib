#pragma once
#include "../etc/Define.h"

class Root
{
public:
	// �R���X�g���N�^
	Root(const std::wstring& fileName);
	// �f�X�g���N�^
	~Root();

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
	// �V�F�[�_�R���p�C��
	long Compile(const std::wstring& fileName);

	// ���[�g���擾
	long RootInfo(void);

	// ���[�g�V�O�l�`������
	long CreateRoot(void);

	// ������
	void Init(const std::wstring& fileName);


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
