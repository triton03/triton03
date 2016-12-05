#include "stdafx.h"
#include "DisplayScore.h"
#include "Player.h"

namespace {
	const CVector2 StrSize = { 125.0f, 43.0f };	//文字のサイズ
	const CVector2 StrPos = { -290.0f, 324.0f };	//文字のポジション
}

DisplayScore::DisplayScore()
{
}


DisplayScore::~DisplayScore()
{
}

void DisplayScore::Start()
{
	m_StrTex.Load("Assets/sprite/score.png");

	m_Str.Init(&m_StrTex);
	m_Str.SetSize(StrSize);
	//ピボットは中央。
	m_Str.SetPivot({ 0.5f, 0.5f });

	m_Str.SetPosition(StrPos);

	for (int i = 0; i < 5; i++) {
		num[i] = NewGO<Number>(0);
	}
	//数字のポジション設定
	num[0]->Init({ -195.0f, StrPos.y });
	num[1]->Init({ -165.0f, StrPos.y });
	num[2]->Init({ -135.0f, StrPos.y });
	num[3]->Init({ -105.0f, StrPos.y });
	num[4]->Init({ -75.0f, StrPos.y });
}
void DisplayScore::Update()
{
	int score = g_player->GetScore();

	num[0]->NumSet(score / 10000);
	score %= 10000;

	num[1]->NumSet(score / 1000);
	score %= 1000;

	num[2]->NumSet(score / 100);
	score %= 100;

	num[3]->NumSet(score / 10);
	score %= 10;

	num[4]->NumSet(score);
}
void DisplayScore::PostRender(CRenderContext& renderContext)
{
	m_Str.Draw(renderContext);
}
