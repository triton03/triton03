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
	score = 100;
}


Coin::~Coin()
{
}

void Coin::Work()
{
	SE = NewGO<CSoundSource>(0);
	SE->Init("Assets/sound/get.wav");
	SE->Play(false);
	g_player->SetScore(score);
	skinModel.SetShadowCasterFlag(false);
	skinModel.SetShadowReceiverFlag(false);
	DeleteGO(this);
}