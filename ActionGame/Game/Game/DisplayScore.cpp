#include "stdafx.h"
#include "DisplayScore.h"
#include "Player.h"

namespace {
	const CVector2 StrSize = { 125.0f, 43.0f };	//�����̃T�C�Y
	const CVector2 StrPos = { -290.0f, 324.0f };	//�����̃|�W�V����
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
	//�s�{�b�g�͒����B
	m_Str.SetPivot({ 0.5f, 0.5f });

	m_Str.SetPosition(StrPos);

	for (int i = 0; i < 5; i++) {
		num[i] = NewGO<Number>(0);
	}
	//�����̃|�W�V�����ݒ�
	num[0]->Init(isInfo,{ -195.0f, StrPos.y });
	num[1]->Init(isInfo,{ -165.0f, StrPos.y });
	num[2]->Init(isInfo,{ -135.0f, StrPos.y });
	num[3]->Init(isInfo,{ -105.0f, StrPos.y });
	num[4]->Init(isInfo,{ -75.0f, StrPos.y });
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

void DisplayScore::DeleteNum()
{
	for (int i = 0; i < 5; i++) {
		DeleteGO(num[i]);
	}
}