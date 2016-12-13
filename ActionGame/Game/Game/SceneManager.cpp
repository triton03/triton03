#include "stdafx.h"
#include "SceneManager.h"
#include "Player.h"
#include "Camera.h"
#include "Interface.h"

SceneManager* scene;

//�}�b�v�̔z�u���
SMapInfo Stage1[] = {
#include "locationInfo.h"	//�X�e�[�W�P
};

SMapInfo Stage2[] = {
#include "locationInfo2.h"	//�X�e�[�W�Q
};

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
				//���[�f�B���O���I������ۂ�
				DeleteGO(start);
				BGMStart();
				state = isStage1;
				flag = false;
			}
			else {
				//�X�e�[�W����
				gameCamera = NewGO<Camera>(0);	//�J�����𐶐�
				map	=NewGO<Map>(0);				//�}�b�v
				g_player = NewGO<Player>(0);	//�v���C���[
				NewGO<Interface>(0);

				StageLoading(isStage1);		//�X�e�[�W�P�̃��[�h

				flag = true;
			}
		}
		break;

	//�X�e�[�W�P
	case isStage1:
	case isStage2:
		//����
		if (g_player->GetInfo() == Player::isDeath) {
			ContinueMenu();
		}

		//�N���A����
		else if (g_player->GetInfo() == Player::isClear) {
			if (isBGM) {
				BGMEnd();
			}
			if (switchFlag) {
				StageChange();
			}
			//�v���C���[����~��ԂɂȂ���
			else if (g_player->isStop()) {
				switching = NewGO<Switching>(0);
				switchFlag = true;
			}
		}
		else {
			switchFlag = false;
		}
		break;
	}
}

//���񂾂Ƃ��̃R���e�B�j���[����
void SceneManager::ContinueMenu()
{
	if (isBGM) {
		BGMEnd();
	}

	if (!g_player->isStop()) { return; }

	if (flag) {
		switchFlag = false;
		g_player->SetFullHP();
		g_player->Reset();
		DeleteGO(gameOver);
		BGMStart();
		flag = false;
	}
	else if (switchFlag) {
		deleteFlag = true;
		if (gameOver->isStart()) {
			deleteFlag = false;
			StageLoading(state);
			flag = true;
		}
	}
	else {
		gameOver = NewGO<GameOver>(0);
		switchFlag = true;
	}
}

void SceneManager::StageChange()
{
	if (flag) {
		//���[�f�B���O���I������ۂ��̂ŏ���

		g_player->Reset();

		DeleteGO(switching);
		switchFlag = false;

		BGMStart();

		state = isStage2;
		flag = false;
	}
	else if (deleteFlag) {
		deleteFlag = false;
		flag = true;

		//�X�e�[�W���[�f�B���O
		StageLoading(isStage2);
	}
	else {
		deleteFlag = true;
	}
}

//�X�e�[�W�ǂݍ���(�ǂݍ��ރX�e�[�W�ԍ�)
void SceneManager::StageLoading(int stage)
{
	int numObject;
	bgm = NewGO<CSoundSource>(0);

	switch (stage) {

	//�X�e�[�W�P
	case isStage1:
		//�}�b�v�ɔz�u����Ă���I�u�W�F�N�g�����v�Z
		numObject = sizeof(Stage1) / sizeof(Stage1[0]);
		map->Create(Stage1, numObject);
		bgm->InitStreaming("Assets/sound/bgm1.wav");
		break;

	//�X�e�[�W�Q
	case isStage2:
		//�}�b�v�ɔz�u����Ă���I�u�W�F�N�g�����v�Z
		numObject = sizeof(Stage2) / sizeof(Stage2[0]);
		map->Create(Stage2, numObject);
		bgm->InitStreaming("Assets/sound/bgm2.wav");
		break;
	}
}

void SceneManager::BGMStart() {
	bgm->Play(true);
	isBGM = true;
}
void SceneManager::BGMEnd() {
	DeleteGO(bgm);
	isBGM = false;
}