#include "stdafx.h"
#include "StartMenu.h"

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

	StartSound = NewGO<CSoundSource>(0);
	StartBGM = NewGO<CSoundSource>(0);
	StartSound->Init("Assets/sound/start.wav");
	StartBGM->InitStreaming("Assets/sound/title.wav");

	StartBGM->Play(true);
}
void StartMenu::Update()
{
	if (!flag && Pad(0).IsTrigger(enButtonStart)) {
		StartBGM->Stop();
		StartSound->Play(false);
		flag = true;
	}
}
void StartMenu::PostRender(CRenderContext& renderContext)
{
	back.Draw(renderContext);
	moji.Draw(renderContext);
}
