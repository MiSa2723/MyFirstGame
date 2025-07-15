#pragma once
#include "Quad.h"

//Quad��6�ʎg����Dice�����A�e�N�X�`���������
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

