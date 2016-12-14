#include "stdafx.h"
#include "SceneManager.h"
#include "Player.h"
#include "Camera.h"
#include "Back.h"

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
	state = isStart;
	StageLoading(isStart);
}

void SceneManager::Update()
{

	switch (state) {

	//スタート画面
	case isStart:
		if (switchFlag) {
			DeleteGO(gameOver);
			switchFlag = false;
		}

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
				gameCamera	= NewGO<Camera>(0);		//カメラを生成
				map			= NewGO<Map>(0);		//マップ
				g_player	= NewGO<Player>(0);		//プレイヤー
				IFace		= NewGO<Interface>(0);	//インターフェース

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
		g_player->ReStart();
		DeleteGO(gameOver);
		BGMStart();
		flag = false;
	}
	else if (switchFlag) {
		deleteFlag = true;
		if (gameOver->isStart()) {
			//続ける
			if (gameOver->GetChoice()) {
				deleteFlag = false;

				g_player->SetFullHP();
				g_player->Reset();

				StageLoading(state);	//ステージ読み込み

				flag = true;
			}
			//やめる
			else {
				StageLoading(isStart);

				DeleteGO(g_player);
				DeleteGO(gameCamera);
				DeleteGO(map);
				DeleteGO(IFace);
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
		//ローディングが終わったぽい
		g_player->ReStart();


		DeleteGO(switching);
		switchFlag = false;

		BGMStart();

		state = isStage2;
		flag = false;
	}
	else if (deleteFlag) {
		deleteFlag = false;
		flag = true;
		
		g_player->Reset();
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
	if (stage == isStart) {
		start = NewGO<StartMenu>(0);
		return;
	}

	int numObject;
	bgm = NewGO<CSoundSource>(0);
	Back* back = NewGO<Back>(0);

	switch (stage) {
	//ステージ１
	case isStage1:
		back->Init("Assets/modelData/Sky.X");

		//マップに配置されているオブジェクト数を計算
		numObject = sizeof(Stage1) / sizeof(Stage1[0]);
		map->Create(Stage1, numObject);
		bgm->InitStreaming("Assets/sound/bgm1.wav");
		break;

	//ステージ２
	case isStage2:
		back->Init("Assets/modelData/Sky2.X");

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