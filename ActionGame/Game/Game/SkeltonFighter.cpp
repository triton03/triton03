/*
	スケルトン
*/

#include "stdafx.h"
#include "SkeltonFighter.h"
#include "Player.h"
#include "Camera.h"

CSkinModelData	FighterSkinModelData;	//スキンモデルデータ
bool			Fighter_flag = false;		//すでに読み込んでいるか

SkeltonFighter::SkeltonFighter()
{
	if (!Fighter_flag) {
		FighterSkinModelData.LoadModelData("Assets/modelData/skelton_fighter.X", NULL);
		Fighter_flag = true;
	}
	skinModelData.CloneModelData(FighterSkinModelData, NULL);
	state.hp = 3;
	state.score = 200;
}

SkeltonFighter::~SkeltonFighter()
{

}
