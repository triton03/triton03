/*
	シーン管理クラス
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

	//フラグ切り替え関数

private:
	void StageChange();		//ステージ変更処理
	void ContinueMenu();
	void StageLoading(int);	//ロード関数
	void BGMStart();		//BGM再生用
	void BGMEnd();			//BGM停止用
	void AllDelete();		//全部消す

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
	TotalResult*	result = nullptr;
	CSoundSource*	bgm;		//BGM
};

extern SceneManager* scene;