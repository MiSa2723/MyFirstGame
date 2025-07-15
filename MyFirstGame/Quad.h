#pragma once
#include "Direct3D.h"
#include <DirectXMath.h>

using namespace DirectX;

//コンスタントバッファ
struct CONSTANT_BUFFER
{
	XMMATRIX matWVP;	//world*view*projectionの行列
	XMMATRIX matW;
};

//頂点情報
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
	ID3D11Buffer* pVertexBuffer_;	//頂点バッファ
	ID3D11Buffer* pIndexBuffer_;	//インデックスバッファ
	ID3D11Buffer* pConstantBuffer_;	//定数バッファ
	Texture* pTexture_;

private:
};