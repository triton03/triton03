#include "stdafx.h"
#include "StartMenu.h"
#include "Player.h"
#include "Map.h"
#include "PlayerHPBar.h"
#include "Camera.h"
#include "BackGround.h"

namespace {
	const CVector2 backSize = { 1280.0f, 720.f };
	const CVector2 backPos = { 0.0f, 0.0f };

	const CVector2 strSize = { 600.0f, 120.f };
	const CVector2 strPos = { 250.0f, -200.0f };
}

StartMenu::StartMenu()
{
}


StartMenu::~StartMenu()
{
}

void StartMenu::Start()
{
//背景
	backTex.Load("Assets/sprite/test.png");
	back.Init(&backTex);
	back.SetSize(backSize);
	back.SetPivot({ 0.5f, 0.5f });		//ピボットは中央
	back.SetPosition(backPos);

//Press Start?
	mojiTex.Load("Assets/sprite/test2.png");
	moji.Init(&mojiTex);
	moji.SetSize(strSize);
	moji.SetPivot({ 0.5f, 0.5f });		//ピボットは中央
	moji.SetPosition(strPos);

	StartSound.Init("Assets/sound/start.wav");
	StartBGM.InitStreaming("Assets/sound/title.wav");
}
void StartMenu::Update()
{
	if (flag) {
		DeleteGO(this);
	}

	StartBGM.Update();
	StartBGM.Play(true);

	if (!flag && Pad(0).IsTrigger(enButtonStart)) {
		StartBGM.Stop();
		StartSound.Play(false);
		flag = true;

		//NewGO<BackGround>(0);
		gameCamera = NewGO<Camera>(0);	//カメラを生成
		g_player = NewGO<Player>(0);	//プレイヤー
		NewGO<Map>(0);					//マップ
		NewGO<PlayerHPBar>(0);
	}

}
void StartMenu::PostRender(CRenderContext& renderContext)
{
	back.Draw(renderContext);
	moji.Draw(renderContext);
}
