#include "stdafx.h"
#include "Coin.h"
#include "Player.h"

CSkinModelData	OriginSkinModelData;	//�X�L�����f���f�[�^
bool			flag = false;

Coin::Coin()
{
	//���f���f�[�^�����[�h
	if (!flag) {
		OriginSkinModelData.LoadModelData("Assets/modelData/coin.x", NULL);
		flag = true;
	}
	//CSkinModel��������
	skinModelData.CloneModelData(OriginSkinModelData, NULL);
}


Coin::~Coin()
{
}

void Coin::Work()
{
	g_player->CoinGet();
	DeleteGO(this);
}