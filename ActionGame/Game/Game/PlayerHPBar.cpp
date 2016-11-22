/*
	プレイヤーのHPバー。
 */

#include "stdafx.h"
#include "PlayerHPBar.h"
#include "Player.h"

namespace {
	const CVector2 hpGaugeMaxSize = { 245.0f, 57.5f };
	const CVector2 hpBarMaxSize = { 230.5f, 40.2f };
	const CVector2 hpBarPos = { -592.95f, 320.0f };
	const CVector2 hpGaugePos = { -600.0f, 320.0f };
}
PlayerHPBar::PlayerHPBar()
{
}
PlayerHPBar::~PlayerHPBar()
{
}
void PlayerHPBar::Start()
{
	m_hpBarTex.Load("Assets/sprite/hp.png");
	m_hpGaugeTex.Load("Assets/sprite/hpsp_bar.png");
	m_hpBarBackTex.Load("Assets/sprite/hp_back.png");

	m_hpBar.Init(&m_hpBarTex);
	m_hpGauge.Init(&m_hpGaugeTex);
	m_hpBarBack.Init(&m_hpBarBackTex);

	m_hpGauge.SetSize(hpGaugeMaxSize);
	m_hpBar.SetSize(hpBarMaxSize);
	m_hpBarBack.SetSize(hpBarMaxSize);
	//ピボットは左中央。
	m_hpBar.SetPivot({ 0.0f, 0.5f });
	m_hpGauge.SetPivot({ 0.0f, 0.5f });
	m_hpBarBack.SetPivot({ 0.0f, 0.5f });

	m_hpBar.SetPosition(hpBarPos);
	m_hpBarBack.SetPosition(hpBarPos);
	m_hpGauge.SetPosition(hpGaugePos);
}
void PlayerHPBar::Update()
{
	CVector2 size = hpBarMaxSize;
	float HP = (float)g_player->GetHP();
	size.x *= (HP / g_player->HP_MAX);
	m_hpBar.SetSize(size);
}
void PlayerHPBar::PostRender(CRenderContext& renderContext)
{
	m_hpGauge.Draw(renderContext);
	m_hpBarBack.Draw(renderContext);
	m_hpBar.Draw(renderContext);
}
