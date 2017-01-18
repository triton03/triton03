#include "stdafx.h"
#include "SceneManager.h"
#include "Player.h"
#include "Camera.h"
#include "Back.h"
#include "ShowSprite.h"

SceneManager* scene;

//�}�b�v�̔z�u���
SMapInfo Stage1[] = {
#include "locationInfo.h"	//�X�e�[�W�P
};

SMapInfo Stage2[] = {
#include "locationInfo2_test.h"	//�X�e�[�W�Q
};

//SMapInfo Stage3[] = {
//#include "locationInfo3.h"	//�X�e�[�W3
//};

SceneManager::SceneManager()
{
}

SceneManager::~SceneManager()
{
}

void SceneManager::Start()
{
	state = isStart;
	StageLoading(isStart);
}

void SceneManager::Update()
{

	switch (state) {

	//�X�^�[�g���
	case isStart:
		//�Q�[���I�[�o�[��ʂ�\�����Ă���
		if (switchFlag) {
			DeleteGO(gameOver);
			switchFlag = false;
		}
		else if (result != nullptr) {
			result->DeleteNum();
			DeleteGO(result);
			result = nullptr;
		}

		//�X�^�[�g�{�^���������ꂽ
		if (start->getFlag()) {
			if (flag) {
				//���[�f�B���O���I������ۂ�
				DeleteGO(start);
				BGMStart();
				state = isStage1;
				flag = false;
				ShowSprite* ss = NewGO<ShowSprite>(0);
				ss->Init(start1);
			}
			else {
				//�X�e�[�W����
				gameCamera	= NewGO<Camera>(0);		//�J�����𐶐�
				map			= NewGO<Map>(0);		//�}�b�v
				g_player	= NewGO<Player>(0);		//�v���C���[
				IFace		= NewGO<Interface>(0);	//�C���^�[�t�F�[�X

				StageLoading(isStage1);		//�X�e�[�W�P�̃��[�h

				flag = true;
			}
		}
		break;

	//�X�e�[�W�P
	case isStage1:
	case isStage2:
	//case isStage3:
		//����
		if (g_player->GetInfo() == Player::isDeath) {
			ContinueMenu();
			PrevBoss = false;
		}
		//�N���A����
		else if (g_player->GetInfo() == Player::isClear) {
			if (isBGM) {
				BGMEnd();
			}
			if (switchFlag) {
				//�X�e�[�W2�ȊO
				if (state != isStage2) {
					StageChange();
				}
				//�X�e�[�W2�̂Ƃ�
				else {
					deleteFlag = true;
					state = isEnd;
				}
			}
			//�v���C���[����~��ԂɂȂ���
			else if (g_player->isStop()) {
				//�X�e�[�W2�ȊO
				if (state != isStage2) {
					switching = NewGO<Switching>(0);
				}
				//�X�e�[�W2�̂Ƃ�
				else {
					StageLoading(isEnd);
				}
				switchFlag = true;
			}
		}
		else {
			switchFlag = false;
		}
		//�{�X��
		if (bossFlag && !PrevBoss) {
			BGMEnd();
			bgm = NewGO<CSoundSource>(0);
			bgm->InitStreaming("Assets/sound/boss.wav");
			BGMStart();
			PrevBoss = true;
			NewGO<BossHP>(0);
		}
		//�{�X�킪�I�����
		else if (!bossFlag && PrevBoss) {
			BGMEnd();
			bgm = NewGO<CSoundSource>(0);
			bgm->InitStreaming("Assets/sound/bgm2.wav");
			BGMStart();
			PrevBoss = false;
		}

		break;

	//�G���f�B���O?
	case isEnd:
		if (deleteFlag) {
			AllDelete();
			deleteFlag = false;
			switchFlag = false;
		}

		if (result->getFlag()) {
			StageLoading(isStart);
			state = isStart;
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
		g_player->ReStart();
		DeleteGO(gameOver);
		BGMStart();
		flag = false;
	}
	else if (switchFlag) {
		deleteFlag = true;
		if (gameOver->isStart()) {
			//������
			if (gameOver->GetChoice()) {
				deleteFlag = false;

				g_player->SetFullHP();
				g_player->Reset();

				StageLoading(state);	//�X�e�[�W�ǂݍ���

				flag = true;
			}
			//��߂�
			else {
				StageLoading(isStart);

				AllDelete();
				deleteFlag = false;

				state = isStart;
			}
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
		//���[�f�B���O���I������ۂ�
		g_player->ReStart();


		DeleteGO(switching);
		switchFlag = false;

		BGMStart();

		state++;
		flag = false;

		ShowSprite* ss = NewGO<ShowSprite>(0);
		ss->Init(start2);
	}
	else if (deleteFlag) {
		deleteFlag = false;
		flag = true;
		
		g_player->Reset();
		//�X�e�[�W���[�f�B���O
		StageLoading(state+1);
	}
	else {
		deleteFlag = true;
	}
}

//�X�e�[�W�ǂݍ���(�ǂݍ��ރX�e�[�W�ԍ�)
void SceneManager::StageLoading(int stage)
{
	//�X�^�[�g���
	if (stage == isStart) {
		start = NewGO<StartMenu>(0);
		return;
	}
	//���U���g���
	else if (stage == isEnd) {
		result = NewGO<TotalResult>(0);
		return;
	}

	int numObject;
	bgm = NewGO<CSoundSource>(0);
	Back* back = NewGO<Back>(0);

	switch (stage) {
	//�X�e�[�W�P
	case isStage1:
		back->Init("Assets/modelData/Sky.X");

		//�}�b�v�ɔz�u����Ă���I�u�W�F�N�g�����v�Z
		numObject = sizeof(Stage1) / sizeof(Stage1[0]);
		map->Create(Stage1, numObject);
		bgm->InitStreaming("Assets/sound/bgm1.wav");
		break;

	//�X�e�[�W�Q
	case isStage2:
		back->Init("Assets/modelData/Sky2.X");

		//�}�b�v�ɔz�u����Ă���I�u�W�F�N�g�����v�Z
		numObject = sizeof(Stage2) / sizeof(Stage2[0]);
		map->Create(Stage2, numObject);
		bgm->InitStreaming("Assets/sound/bgm2.wav");
		break;

	/*
	//�X�e�[�W�R
	case isStage3:
		back->Init("Assets/modelData/Sky2.X");

		//�}�b�v�ɔz�u����Ă���I�u�W�F�N�g�����v�Z
		numObject = sizeof(Stage3) / sizeof(Stage3[0]);
		map->Create(Stage3, numObject);
		bgm->InitStreaming("Assets/sound/bgm3.wav");
		break;
	*/
	}

}

void SceneManager::AllDelete()
{
	IFace->DeleteIF();
	DeleteGO(IFace);
	DeleteGO(g_player);
	DeleteGO(map);
	DeleteGO(gameCamera);
}

void SceneManager::BGMStart() {
	bgm->Play(true);
	isBGM = true;
}
void SceneManager::BGMEnd() {
	DeleteGO(bgm);
	isBGM = false;
}