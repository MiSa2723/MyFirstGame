#pragma once
#include "Direct3D.h"
#include <DirectXMath.h>

using namespace DirectX;

//コンスタントバッファ
struct CONSTANT_BUFFER
{
	DirectX::XMMATRIX matWVP;	//world*view*projectionの行列
};

//頂点情報
struct VERTEX
{
	XMVECTOR position;
	XMVECTOR uv;
};

class Texture;

class Quad
{
	ID3D11Buffer* pVertexBuffer_;	//頂点バッファ
	ID3D11Buffer* pIndexBuffer_;	//インデックスバッファ
	ID3D11Buffer* pConstantBuffer_;	//定数バッファ
	Texture* pTexture_;

public:
	Quad();
	~Quad();
	HRESULT Initialize();
	void Draw(XMMATRIX& worldMatrix);
	void Release();
};