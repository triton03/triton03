#include "stdafx.h"
#include "GameOver.h"
#include "SceneManager.h"

namespace {
	const CVector2 backSize = { 1280.0f, 720.f };
	const CVector2 backPos = { 0.0f, 0.0f };

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
	//�w�i
	backTex.Load("Assets/sprite/GameOver.png");
	back.Init(&backTex);
	back.SetSize(backSize);
	back.SetPivot({ 0.5f, 0.5f });		//�s�{�b�g�͒���
	back.SetPosition(backPos);

	//�I���̖��
	choiceTex.Load("Assets/sprite/choice.png");
	choice.Init(&choiceTex);
	choice.SetSize(C_Size);
	choice.SetPivot({ 0.5f, 0.5f });		//�s�{�b�g�͒���
	choice.SetPosition(C_PosUP);

	//�T�E���h
	SE = NewGO<CSoundSource>(0);
	SE->Init("Assets/sound/next.wav");

	isChoice = true;
	flag	= false;
}
void GameOver::Update()
{
	//�������Ȃ�?
	if (flag) { return; }

	float input = Pad(0).GetLStickYF();

	//��I��(�Â���)
	if (input > 0.0 || Pad(0).IsTrigger(enButtonUp)) {
		isChoice = true;
		choice.SetPosition(C_PosUP);
	}
	//���I��(�����)
	else if (input < 0.0 || Pad(0).IsTrigger(enButtonDown)) {
		isChoice = false;
		choice.SetPosition(C_PosDown);
	}

	//����
	if(Pad(0).IsTrigger(enButtonB)){
		flag = true;
	}
}
void GameOver::PostRender(CRenderContext& renderContext)
{
	back.Draw(renderContext);
	choice.Draw(renderContext);
}