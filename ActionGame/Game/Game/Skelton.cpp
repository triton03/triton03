/*
	�X�P���g��
*/

#include "stdafx.h"
#include "Skelton.h"
#include "Player.h"
#include "Camera.h"

CSkinModelData	SkeltonSkinModelData;	//�X�L�����f���f�[�^
bool			Skelton_flag = false;		//���łɓǂݍ���ł��邩

Skelton::Skelton()
{
	if (!Skelton_flag) {
		SkeltonSkinModelData.LoadModelData("Assets/modelData/skelton.X", NULL);
		Skelton_flag = true;
	}
	skinModelData.CloneModelData(SkeltonSkinModelData, NULL);
	state.hp = 1;
	state.score = 150;
}

Skelton::~Skelton()
{

}

void Skelton::Move()
{
	move = characterController.GetMoveSpeed();
	if (timer > 1.8f) {
		move.y = 12.0f;
		characterController.Jump();
		timer = 0.0f;
	}

	timer += GameTime().GetFrameDeltaTime();
}
