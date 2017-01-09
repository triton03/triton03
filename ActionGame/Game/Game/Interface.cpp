#include "stdafx.h"
#include "Interface.h"
#include "SceneManager.h"

namespace {
	const CVector2 InfoBackSize = { 620.0f, 125.0f };	//バックのサイズ
	const CVector2 InfoBackPos = { -640.0f, 360.0f };	//バックのポジション
}

Interface::Interface()
{
}


Interface::~Interface()
{

}

void Interface::Start()
{
	m_InfoBackTex.Load("Assets/sprite/interface.png");

	m_InfoBack.Init(&m_InfoBackTex);
	m_InfoBack.SetSize(InfoBackSize);
	//ピボットは左上。
	m_InfoBack.SetPivot({ 0.0f, 1.0f });

	m_InfoBack.SetPosition(InfoBackPos);

	Bar = NewGO<PlayerHPBar>(0);
	DScore = NewGO<DisplayScore>(0);
	DTime = NewGO<DisplayTime>(0);
}
void Interface::Update()
{

}
void Interface::PostRender(CRenderContext& renderContext)
{
	if (scene->isDelete()) { return; }

	m_InfoBack.Draw(renderContext);
}

void Interface::DeleteIF()
{
	DeleteGO(Bar);
	DScore->DeleteNum();
	DeleteGO(DScore);
	DTime->DeleteNum();
	DeleteGO(DTime);
}