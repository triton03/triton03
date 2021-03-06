#include "stdafx.h"
#include "GameOver.h"
#include "SceneManager.h"

namespace {
	const CVector2 C_Size = { 191.0f,127.0f };
	const CVector2 C_PosUP = { 160.0f,-70.0f };
	const CVector2 C_PosDown = { 160.0f,-220.0f };
}

GameOver::GameOver()
{
}

GameOver::~GameOver()
{
}

void GameOver::Start()
{
	//背景
	backTex.Load("Assets/sprite/GameOver.png");
	back.Init(&backTex);
	back.SetSize(backSize);
	back.SetPivot({ 0.5f, 0.5f });		//ピボットは中央
	back.SetPosition(backPos);

	//選択の矢印
	choiceTex.Load("Assets/sprite/choice.png");
	choice.Init(&choiceTex);
	choice.SetSize(C_Size);
	choice.SetPivot({ 0.5f, 0.5f });		//ピボットは中央
	choice.SetPosition(C_PosUP);

	isChoice = true;
	flag	= false;
}
void GameOver::Update()
{
	//何もしない?
	if (flag) { return; }

	float input = Pad(0).GetLStickYF();

	//上選択(つづける)
	if (input > 0.0 || Pad(0).IsTrigger(enButtonUp)) {
		isChoice = true;
		choice.SetPosition(C_PosUP);
	}
	//下選択(おわる)
	else if (input < 0.0 || Pad(0).IsTrigger(enButtonDown)) {
		isChoice = false;
		choice.SetPosition(C_PosDown);
	}

	//決定
	if(Pad(0).IsTrigger(enButtonB)){
		//サウンド
		CSoundSource* SE = NewGO<CSoundSource>(0);
		SE->Init("Assets/sound/next.wav");
		SE->Play(false);
		flag = true;
	}
}
void GameOver::PostRender(CRenderContext& renderContext)
{
	back.Draw(renderContext);
	choice.Draw(renderContext);
}