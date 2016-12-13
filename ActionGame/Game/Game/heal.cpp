#include "stdafx.h"
#include "heal.h"
#include "Player.h"

CSkinModelData	h_OriginSkinModelData;	//スキンモデルデータ
bool			h_flag = false;

Heal::Heal()
{
	//モデルデータをロード
	if (!h_flag) {
		h_OriginSkinModelData.LoadModelData("Assets/modelData/item.x", NULL);
		h_flag = true;
	}
	//CSkinModelを初期化
	skinModelData.CloneModelData(h_OriginSkinModelData, NULL);
}


Heal::~Heal()
{
}

void Heal::Work()
{
	if (g_player->healing()) {
		SE = NewGO<CSoundSource>(0);
		SE->Init("Assets/sound/cure.wav");
		SE->Play(false);
		DeleteGO(this);
	}
}