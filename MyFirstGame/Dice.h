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
	HRESULT Initialize() override;
	void Draw(XMMATRIX& worldMatrix) override;
	void Release();
};

