#include "stdafx.h"
#include "TotalResult.h"
#include "Player.h"
#include "SceneManager.h"


TotalResult::TotalResult()
{
}


TotalResult::~TotalResult()
{

}

void TotalResult::Start()
{
/*�w�i����*/
	backTex.Load("Assets/sprite/result.png");
	back.Init(&backTex);
	back.SetSize(backSize);
	back.SetPivot({ 0.5f, 0.5f });		//�s�{�b�g�͒���
	back.SetPosition(backPos);

/*�^�C���\������*/

	for (int i = 0; i < 4; i++) {
		timeNum[i] = NewGO<Number>(0);
	}

	//�R�����̏���
	m_colonTex.Load("Assets/sprite/resultNum/colon.png");
	m_colon.Init(&m_colonTex);
	m_colon.SetSize({ 33.0f, 88.0f });
	//�s�{�b�g�͒����B
	m_colon.SetPivot({ 0.5f, 0.5f });

	//�����̃|�W�V�����ݒ�
	timeNum[0]->Init(isResult,{ -20.0f, time_Y }, ResultNumSize);
	timeNum[1]->Init(isResult,{ 50.0f, time_Y }, ResultNumSize);
	m_colon.SetPosition({ 105.0f, time_Y });
	timeNum[2]->Init(isResult, { 160.0f, time_Y }, ResultNumSize);
	timeNum[3]->Init(isResult, { 230.0f, time_Y }, ResultNumSize);

	int time = (int)(g_player->GetTotalTime());

	timeNum[0]->NumSet((time / 600));
	time %= 600;

	timeNum[1]->NumSet((time / 60));
	time %= 60;

	timeNum[2]->NumSet(time / 10);
	time %= 10;

	timeNum[3]->NumSet(time);

/*�X�R�A�\������*/
	for (int i = 0; i < 5; i++) {
		scoreNum[i] = NewGO<Number>(0);
	}
	//�����̃|�W�V�����ݒ�
	scoreNum[0]->Init(isResult, { -20.0f, score_Y }, ResultNumSize);
	scoreNum[1]->Init(isResult, { 50.0f, score_Y }, ResultNumSize);
	scoreNum[2]->Init(isResult, { 120.0f, score_Y }, ResultNumSize);
	scoreNum[3]->Init(isResult, { 190.0f, score_Y }, ResultNumSize);
	scoreNum[4]->Init(isResult, { 260.0f, score_Y }, ResultNumSize);

	int score = g_player->GetTotalScore();

	scoreNum[0]->NumSet(score / 10000);
	score %= 10000;

	scoreNum[1]->NumSet(score / 1000);
	score %= 1000;

	scoreNum[2]->NumSet(score / 100);
	score %= 100;

	scoreNum[3]->NumSet(score / 10);
	score %= 10;

	scoreNum[4]->NumSet(score);

/*�T�E���h����*/
	Sound = NewGO<CSoundSource>(0);
	BGM = NewGO<CSoundSource>(0);
	Sound->Init("Assets/sound/next.wav");
	BGM->InitStreaming("Assets/sound/result.wav");

	BGM->Play(true);
}
void TotalResult::Update()
{
	if (Pad(0).IsTrigger(enButtonStart) && (!flag)) {
		DeleteGO(BGM);
		Sound->Play(false);
		flag = true;
	}
}
void TotalResult::PostRender(CRenderContext& renderContext)
{
	back.Draw(renderContext);
	m_colon.Draw(renderContext);
}

void TotalResult::DeleteNum() {
	for (int i = 0; i < 4; i++) {
		DeleteGO(timeNum[i]);
	}
	for (int i = 0; i < 5; i++) {
		DeleteGO(scoreNum[i]);
	}
}