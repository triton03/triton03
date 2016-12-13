#include "stdafx.h"
#include "heal.h"
#include "Player.h"

CSkinModelData	h_OriginSkinModelData;	//�X�L�����f���f�[�^
bool			h_flag = false;

Heal::Heal()
{
	//���f���f�[�^�����[�h
	if (!h_flag) {
		h_OriginSkinModelData.LoadModelData("Assets/modelData/item.x", NULL);
		h_flag = true;
	}
	//CSkinModel��������
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