#include "stdafx.h"
#include "Interface.h"
#include "PlayerHPBar.h"
#include "Number.h"

namespace {
	const CVector2 InfoBackSize = { 550.0f, 150.5f };	//サイズ
	const CVector2 InfoBackPos = { -640.0f, 360.0f };	//ポジション
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

	NewGO<PlayerHPBar>(0);
}
void Interface::Update()
{

}
void Interface::PostRender(CRenderContext& renderContext)
{
	m_InfoBack.Draw(renderContext);
}
