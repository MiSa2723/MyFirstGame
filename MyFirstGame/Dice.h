#pragma once
#include "Quad.h"

//Quadを6面使ってDiceを作る、テクスチャも作って
class Dice :
    public Quad
{
	Texture* pDiceTexture_;

public:
	Dice();
	~Dice();
	HRESULT Initialize();
	void Draw(XMMATRIX& worldMatrix);
	void Release();
};

