/*
	�X�P���g���t�@�C�^�[
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
	state.hp = 2;
	state.score = 200;
}

SkeltonFighter::~SkeltonFighter()
{

}

void SkeltonFighter::Move()
{
	if (length > 20.0f) 
	{ 
		move.x = 0.0f;
		move.z = 0.0f;
		return; 
	}
	CVector3 diff;

	diff.Subtract(g_player->GetPosition(), centralPos);
	diff.Normalize();	//�����x�N�g���ɕϊ�
	
	move.x = diff.x*speed;
	move.z = diff.z*speed;

	rotation.SetRotation(CVector3::AxisY, atan2f(diff.x, diff.z));

	if (timer == 0.0f) {
		move.y = 12.0f;
		characterController.Jump();
	}

	timer += GameTime().GetFrameDeltaTime();

	if (timer > 2.0f) {

		timer = 0.0f;
	}
}
