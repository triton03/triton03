/*
	シーン管理クラス
*/
#include "Map.h"
#include "StartMenu.h"
#include "Switching.h"
#include "GameOver.h"
#include "Interface.h"

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

	bool isDelete() {
		return deleteFlag;
	}

	//フラグ切り替え関数

private:
	void StageChange();
	void ContinueMenu();
	void StageLoading(int);
	void BGMStart();
	void BGMEnd();

	bool		flag = false;	//汎用フラグ
	bool		deleteFlag = false;	//マップチップ消去フラグ
	bool		switchFlag = false;
	bool		isBGM = false;

	int				state;
	float			timer = 0.0f;	//タイマー。

	Map*			map;
	StartMenu*		start;
	Interface*		IFace;
	Switching*		switching;
	GameOver*		gameOver;
	CSoundSource*	bgm;		//BGM
};

extern SceneManager* scene;