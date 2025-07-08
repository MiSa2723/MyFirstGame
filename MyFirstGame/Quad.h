#pragma once
#include "Direct3D.h"
#include <DirectXMath.h>

using namespace DirectX;

//�R���X�^���g�o�b�t�@
struct CONSTANT_BUFFER
{
	DirectX::XMMATRIX matWVP;	//world*view*projection�̍s��
};

//���_���
struct VERTEX
{
	XMVECTOR position;
	XMVECTOR uv;
};

class Texture;

class Quad
{
	ID3D11Buffer* pVertexBuffer_;	//���_�o�b�t�@
	ID3D11Buffer* pIndexBuffer_;	//�C���f�b�N�X�o�b�t�@
	ID3D11Buffer* pConstantBuffer_;	//�萔�o�b�t�@
	Texture* pTexture_;

public:
	Quad();
	~Quad();
	HRESULT Initialize();
	void Draw(XMMATRIX& worldMatrix);
	void Release();
};