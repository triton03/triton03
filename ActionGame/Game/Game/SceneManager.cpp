#include "stdafx.h"
#include "SceneManager.h"
#include "Player.h"
#include "Camera.h"
#include "Interface.h"


SceneManager* scene;

SceneManager::SceneManager()
{
}


SceneManager::~SceneManager()
{
}

void SceneManager::Start()
{
	start = NewGO<StartMenu>(0);
	state = isStart;
}

void SceneManager::Update()
{
	switch (state) {

	//�X�^�[�g���
	case isStart:
		//�X�^�[�g�{�^���������ꂽ
		if (start->getFlag()) {
			if (flag) {
				//���[�f�B���O���I������ۂ��̂ŏ���
				DeleteGO(start);
				state = isStage1;
				flag = false;
			}
			else {
				//�X�e�[�W����
				gameCamera = NewGO<Camera>(0);	//�J�����𐶐�
				map=NewGO<Map>(0);					//�}�b�v

				g_player = NewGO<Player>(0);	//�v���C���[
				NewGO<Interface>(0);

				flag = true;
			}
		}
		break;

	//�X�e�[�W�P
	case isStage1:
		
		if (switchFlag) {
			StageChange();
		}
		//�v���C���[����~��ԂɂȂ������N���A����
		else if (g_player->GetInfo() == Player::isStop) {
			switching=NewGO<Switching>(0);
			switchFlag = true;
		}
		break;
	}
}

void SceneManager::StageChange()
{
	if (flag) {
		//���[�f�B���O���I������ۂ��̂ŏ���

		DeleteGO(switching);
		switchFlag = false;

		g_player->Reset();
		state = isStage1;
		flag = false;
	}
	else if (deleteFlag) {
		deleteFlag = false;
		DeleteGO(map);
		map = NewGO<Map>(0);
		flag = true;
	}
	else {
		deleteFlag = true;
	}
}