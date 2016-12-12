#include "stdafx.h"
#include "Coin.h"
#include "Player.h"

CSkinModelData	OriginSkinModelData;	//スキンモデルデータ
bool			flag = false;

Coin::Coin()
{
	//モデルデータをロード
	if (!flag) {
		OriginSkinModelData.LoadModelData("Assets/modelData/coin.x", NULL);
		flag = true;
	}
	//CSkinModelを初期化
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