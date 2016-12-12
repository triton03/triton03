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

	//スタート画面
	case isStart:
		//スタートボタンが押された
		if (start->getFlag()) {
			if (flag) {
				//ローディングが終わったぽいので消す
				DeleteGO(start);
				state = isStage1;
				flag = false;
			}
			else {
				//ステージ生成
				gameCamera = NewGO<Camera>(0);	//カメラを生成
				map=NewGO<Map>(0);					//マップ

				g_player = NewGO<Player>(0);	//プレイヤー
				NewGO<Interface>(0);

				flag = true;
			}
		}
		break;

	//ステージ１
	case isStage1:
		
		if (switchFlag) {
			StageChange();
		}
		//プレイヤーが停止状態になった→クリアした
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
		//ローディングが終わったぽいので消す

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