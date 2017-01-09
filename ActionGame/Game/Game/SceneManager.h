/*
	�V�[���Ǘ��N���X
*/
#include "Map.h"
#include "StartMenu.h"
#include "Switching.h"
#include "GameOver.h"
#include "Interface.h"
#include "TotalResult.h"

#pragma once

enum State {
	isStart,
	isStage1,
	isStage2,
	isStage3,
	isEnd,
};

class SceneManager : public IGameObject
{
public:
	SceneManager();
	~SceneManager();
	void Start();
	void Update();

	bool isDelete() {
		return deleteFlag;
	}

	//�t���O�؂�ւ��֐�

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