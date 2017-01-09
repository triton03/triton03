#include "stdafx.h"
#include "SkeltonMage.h"
#include "EnemyBullet.h"

CSkinModelData	MageSkinModelData;	//スキンモデルデータ
bool			Mage_flag = false;		//すでに読み込んでいるか

SkeltonMage::SkeltonMage()
{
	if (!Mage_flag) {
		MageSkinModelData.LoadModelData("Assets/modelData/skelton_mage.X", NULL);
		Mage_flag = true;
	}
	skinModelData.CloneModelData(MageSkinModelData, NULL);
	state.hp = 2;
	state.score = 200;

	//弾のモデルデータをロード(1回だけ)
	if (!eb_flag) {
		eb_OriginSkinModelData.LoadModelData("Assets/modelData/e_bullet.x", NULL);
		eb_flag = true;
	}
}


SkeltonMage::~SkeltonMage()
{
}

void SkeltonMage::Move() 
{
	if (timer > 0.9f) {
		EnemyBullet* bullet = NewGO<EnemyBullet>(0);
		bullet->Init(centralPos);
		timer = 0.0f;
	}

	timer += GameTime().GetFrameDeltaTime();
}
