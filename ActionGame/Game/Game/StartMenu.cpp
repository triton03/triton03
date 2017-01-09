#include "stdafx.h"
#include "StartMenu.h"

namespace {
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
//�w�i
	backTex.Load("Assets/sprite/test.png");
	back.Init(&backTex);
	back.SetSize(backSize);
	back.SetPivot({ 0.5f, 0.5f });		//�s�{�b�g�͒���
	back.SetPosition(backPos);

//Press Start?
	mojiTex.Load("Assets/sprite/test2.png");
	moji.Init(&mojiTex);
	moji.SetSize(strSize);
	moji.SetPivot({ 0.5f, 0.5f });		//�s�{�b�g�͒���
	moji.SetPosition(strPos);

//Press Start?(����)
	mojiTex2.Load("Assets/sprite/test3.png");
	moji2.Init(&mojiTex2);
	moji2.SetSize(strSize);
	moji2.SetPivot({ 0.5f, 0.5f });		//�s�{�b�g�͒���
	moji2.SetPosition(strPos);

	StartSound = NewGO<CSoundSource>(0);
	StartBGM = NewGO<CSoundSource>(0);
	StartSound->Init("Assets/sound/start.wav");
	StartBGM->InitStreaming("Assets/sound/title.wav");

	StartBGM->Play(true);
}
void StartMenu::Update()
{
	timer += GameTime().GetFrameDeltaTime();
	if (timer > 1.0f) { timer = 0.0f; }

	if (Pad(0).IsTrigger(enButtonStart) && (!flag)) {
		DeleteGO(StartBGM);
		StartSound->Play(false);
		flag = true;
	}
}
void StartMenu::PostRender(CRenderContext& renderContext)
{
	back.Draw(renderContext);
	if (flag) {
		moji2.Draw(renderContext);
	}
	else {
		
		if (timer >0 && timer <=0.7) {
			moji.Draw(renderContext);
		}
	}
}
