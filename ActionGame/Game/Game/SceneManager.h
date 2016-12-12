/*
	�V�[���Ǘ��N���X
*/
#include "Map.h"
#include "StartMenu.h"
#include "Switching.h"

#pragma once

enum State {
	isStart,
	isStage1,
	isStage2,
	isEnd,
};

class SceneManager : public IGameObject
{
public:
	SceneManager();
	~SceneManager();
	void Start();
	void Update();
	void StageChange();

	bool isDelete() {
		return deleteFlag;
	}

	//�t���O�؂�ւ��֐�
	bool FlagSwitching() {
		flag = !flag;
	}

private:
	bool		flag = false;	//�ėp�t���O
	bool		deleteFlag = false;	//�}�b�v�`�b�v�����t���O
	bool		switchFlag = false;

	int				state;
	float			timer = 0.0f;	//�^�C�}�[�B

	Map*			map;
	StartMenu*		start;
	Switching*		switching;
};

extern SceneManager* scene;