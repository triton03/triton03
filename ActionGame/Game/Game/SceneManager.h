/*
	�V�[���Ǘ��N���X
*/
#include "Map.h"
#include "StartMenu.h"
#include "Switching.h"
#include "GameOver.h"
#include "Interface.h"
#include "TotalResult.h"
#include "BossHP.h"

#pragma once

enum isStage {
	isStart,
	isStage1,
	isStage2,
	//isStage3,
	isEnd,
};

class SceneManager : public IGameObject
{
public:
	SceneManager();
	~SceneManager();
	void Start();
	void Update();

	//�폜�t���O�擾
	bool isDelete() 
	{
		return deleteFlag;
	}
	//�{�X�t���O�擾
	bool getBossFlag()
	{
		return bossFlag;
	}

	//�{�X�t���O�ݒ�
	void setBossFlag(bool flag)
	{
		bossFlag = flag;
	}

	int getStage()
	{
		return state;
	}

private:
	void StageChange();		//�X�e�[�W�ύX����
	void ContinueMenu();
	void StageLoading(int);	//���[�h�֐�
	void BGMStart();		//BGM�Đ��p
	void BGMEnd();			//BGM��~�p
	void AllDelete();		//�S������

	bool		flag = false;	//�ėp�t���O
	bool		deleteFlag = false;	//�}�b�v�`�b�v�����t���O
	bool		switchFlag = false;
	bool		isBGM = false;
	bool		bossFlag = false;
	bool		PrevBoss = false;

	int				state;
	float			timer = 0.0f;	//�^�C�}�[�B

	Map*			map;
	StartMenu*		start;
	Interface*		IFace;
	Switching*		switching;
	GameOver*		gameOver;
	TotalResult*	result = nullptr;
	CSoundSource*	bgm;		//BGM
};

extern SceneManager* scene;