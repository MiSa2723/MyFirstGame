#pragma once
#include "Direct3D.h"
#include <DirectXMath.h>

using namespace DirectX;

//�R���X�^���g�o�b�t�@
struct CONSTANT_BUFFER
{
	XMMATRIX matWVP;	//world*view*projection�̍s��
	XMMATRIX matW;
};

//���_���
struct VERTEX
{
	XMVECTOR position;
	XMVECTOR uv;
	XMVECTOR normal;
};

class Texture;

class Quad
{
public:
	Quad();
	virtual ~Quad();
	virtual HRESULT Initialize();
	virtual void Draw(XMMATRIX& worldMatrix);
	void Release();

protected:
	ID3D11Buffer* pVertexBuffer_;	//���_�o�b�t�@
	ID3D11Buffer* pIndexBuffer_;	//�C���f�b�N�X�o�b�t�@
	ID3D11Buffer* pConstantBuffer_;	//�萔�o�b�t�@
	Texture* pTexture_;

private:
};