#include "stdafx.h"
#include "SceneManager.h"
#include "Player.h"
#include "Camera.h"
#include "Interface.h"

SceneManager* scene;

//マップの配置情報
SMapInfo Stage1[] = {
#include "locationInfo.h"	//ステージ１
};

SMapInfo Stage2[] = {
#include "locationInfo2.h"	//ステージ２
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

	//スタート画面
	case isStart:
		//スタートボタンが押された
		if (start->getFlag()) {
			if (flag) {
				//ローディングが終わったぽい
				DeleteGO(start);
				BGMStart();
				state = isStage1;
				flag = false;
			}
			else {
				//ステージ生成
				gameCamera = NewGO<Camera>(0);	//カメラを生成
				map	=NewGO<Map>(0);				//マップ
				g_player = NewGO<Player>(0);	//プレイヤー
				NewGO<Interface>(0);

				StageLoading(isStage1);		//ステージ１のロード

				flag = true;
			}
		}
		break;

	//ステージ１
	case isStage1:
	case isStage2:
		//死んだ
		if (g_player->GetInfo() == Player::isDeath) {
			ContinueMenu();
		}

		//クリアした
		else if (g_player->GetInfo() == Player::isClear) {
			if (isBGM) {
				BGMEnd();
			}
			if (switchFlag) {
				StageChange();
			}
			//プレイヤーが停止状態になった
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

//死んだときのコンティニュー処理
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
		//ローディングが終わったぽいので消す

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

		//ステージローディング
		StageLoading(isStage2);
	}
	else {
		deleteFlag = true;
	}
}

//ステージ読み込み(読み込むステージ番号)
void SceneManager::StageLoading(int stage)
{
	int numObject;
	bgm = NewGO<CSoundSource>(0);

	switch (stage) {

	//ステージ１
	case isStage1:
		//マップに配置されているオブジェクト数を計算
		numObject = sizeof(Stage1) / sizeof(Stage1[0]);
		map->Create(Stage1, numObject);
		bgm->InitStreaming("Assets/sound/bgm1.wav");
		break;

	//ステージ２
	case isStage2:
		//マップに配置されているオブジェクト数を計算
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