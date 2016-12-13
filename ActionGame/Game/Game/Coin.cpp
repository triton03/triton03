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
	DeleteGO(this);
}