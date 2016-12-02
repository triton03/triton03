#include "stdafx.h"
#include "DisplayTime.h"

namespace {
	const CVector2 StrSize = { 110.0f, 43.0f };	//文字のサイズ
	const CVector2 StrPos = { -290.0f, 270.0f };	//文字のポジション
}

DisplayTime::DisplayTime()
{
}


DisplayTime::~DisplayTime()
{
}

void DisplayTime::Start()
{
	m_StrTex.Load("Assets/sprite/time.png");

	m_Str.Init(&m_StrTex);
	m_Str.SetSize(StrSize);
	//ピボットは中央。
	m_Str.SetPivot({ 0.5f, 0.5f });
	m_Str.SetPosition(StrPos);

	for (int i = 0; i < 4; i++) {
		num[i] = NewGO<Number>(0);
	}

	//コロンの準備
	m_colonTex.Load("Assets/sprite/colon.png");
	m_colon.Init(&m_colonTex);
	m_colon.SetSize({ 15.0f, 40.0f });
	//ピボットは中央。
	m_colon.SetPivot({ 0.5f, 0.5f });

	//数字のポジション設定
	num[0]->Init({ -195.0f, StrPos.y });
	num[1]->Init({ -165.0f, StrPos.y });
	m_colon.SetPosition({ -130.0f, StrPos.y });
	num[2]->Init({ -100.0f, StrPos.y });
	num[3]->Init({ -70.0f, StrPos.y });
}
void DisplayTime::Update()
{

}
void DisplayTime::PostRender(CRenderContext& renderContext)
{
	m_Str.Draw(renderContext);
	m_colon.Draw(renderContext);
}
