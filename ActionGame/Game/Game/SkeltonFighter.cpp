/*
	�X�P���g��
*/

#include "stdafx.h"
#include "SkeltonFighter.h"
#include "Player.h"
#include "Camera.h"

CSkinModelData	FighterSkinModelData;	//�X�L�����f���f�[�^
bool			Fighter_flag = false;		//���łɓǂݍ���ł��邩

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
