#include "stdafx.h"
#include "SceneManager.h"
#include "Player.h"
#include "Camera.h"
#include "Back.h"
#include "ShowSprite.h"

SceneManager* scene;

//マップの配置情報
SMapInfo Stage1[] = {
#include "locationInfo.h"	//ステージ１
};

SMapInfo Stage2[] = {
#include "locationInfo2_test.h"	//ステージ２
};

//SMapInfo Stage3[] = {
//#include "locationInfo3.h"	//ステージ3
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

	//スタート画面
	case isStart:
		//ゲームオーバー画面を表示してたら
		if (switchFlag) {
			DeleteGO(gameOver);
			switchFlag = false;
		}
		else if (result != nullptr) {
			result->DeleteNum();
			DeleteGO(result);
			result = nullptr;
		}

		//スタートボタンが押された
		if (start->getFlag()) {
			if (flag) {
				//ローディングが終わったぽい
				DeleteGO(start);
				BGMStart();
				state = isStage1;
				flag = false;
				ShowSprite* ss = NewGO<ShowSprite>(0);
				ss->Init(start1);
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
	//case isStage3:
		//死んだ
		if (g_player->GetInfo() == Player::isDeath) {
			ContinueMenu();
			PrevBoss = false;
		}
		//クリアした
		else if (g_player->GetInfo() == Player::isClear) {
			if (isBGM) {
				BGMEnd();
			}
			if (switchFlag) {
				//ステージ2以外
				if (state != isStage2) {
					StageChange();
				}
				//ステージ2のとき
				else {
					deleteFlag = true;
					state = isEnd;
				}
			}
			//プレイヤーが停止状態になった
			else if (g_player->isStop()) {
				//ステージ2以外
				if (state != isStage2) {
					switching = NewGO<Switching>(0);
				}
				//ステージ2のとき
				else {
					StageLoading(isEnd);
				}
				switchFlag = true;
			}
		}
		else {
			switchFlag = false;
		}
		//ボス戦
		if (bossFlag && !PrevBoss) {
			BGMEnd();
			bgm = NewGO<CSoundSource>(0);
			bgm->InitStreaming("Assets/sound/boss.wav");
			BGMStart();
			PrevBoss = true;
			NewGO<BossHP>(0);
		}
		//ボス戦が終わった
		else if (!bossFlag && PrevBoss) {
			BGMEnd();
			bgm = NewGO<CSoundSource>(0);
			bgm->InitStreaming("Assets/sound/bgm2.wav");
			BGMStart();
			PrevBoss = false;
		}

		break;

	//エンディング?
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
		//ローディングが終わったぽい
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
		//ステージローディング
		StageLoading(state+1);
	}
	else {
		deleteFlag = true;
	}
}

//ステージ読み込み(読み込むステージ番号)
void SceneManager::StageLoading(int stage)
{
	//スタート画面
	if (stage == isStart) {
		start = NewGO<StartMenu>(0);
		return;
	}
	//リザルト画面
	else if (stage == isEnd) {
		result = NewGO<TotalResult>(0);
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

	/*
	//ステージ３
	case isStage3:
		back->Init("Assets/modelData/Sky2.X");

		//マップに配置されているオブジェクト数を計算
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