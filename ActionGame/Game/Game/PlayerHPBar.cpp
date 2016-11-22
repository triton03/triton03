/*
	プレイヤーのHPバー。
 */

#include "stdafx.h"
#include "PlayerHPBar.h"
#include "Player.h"

namespace {
	const CVector2 hpGaugeMaxSize = { 245.0f, 67.5f };
	const CVector2 hpBarMaxSize = { 230.5f, 50.2f };
	const CVector2 hpBarPos = { -592.95f, 320.0f };
	const CVector2 hpGaugePos = { -600.0f, 320.0f };

	const CVector2 hpHeartSize = { 76.83f, 50.2f };
	const CVector2 hpHeartPos1 = { -592.95f, 320.0f };
	const CVector2 hpHeartPos2 = { -516.12f, 320.0f };
	const CVector2 hpHeartPos3 = { -439.29f, 320.0f };
}
PlayerHPBar::PlayerHPBar()
{
}
PlayerHPBar::~PlayerHPBar()
{
}
void PlayerHPBar::Start()
{
	m_hpHeartTex.Load("Assets/sprite/hp.png");
	m_hpGaugeTex.Load("Assets/sprite/hpsp_bar.png");
	m_hpBarBackTex.Load("Assets/sprite/hp_back.png");

	for (int i = 0; i < 3; i++) {
		m_hpHeart[i].Init(&m_hpHeartTex);
		m_hpHeart[i].SetSize(hpHeartSize);
		m_hpHeart[i].SetPivot({ 0.0f, 0.5f });
	}
	m_hpHeart[0].SetPosition(hpHeartPos1);
	m_hpHeart[1].SetPosition(hpHeartPos2);
	m_hpHeart[2].SetPosition(hpHeartPos3);

	m_hpGauge.Init(&m_hpGaugeTex);
	m_hpBarBack.Init(&m_hpBarBackTex);

	m_hpGauge.SetSize(hpGaugeMaxSize);

	m_hpBarBack.SetSize(hpBarMaxSize);
	//ピボットは左中央。
	m_hpGauge.SetPivot({ 0.0f, 0.5f });
	m_hpBarBack.SetPivot({ 0.0f, 0.5f });

	m_hpBarBack.SetPosition(hpBarPos);
	m_hpGauge.SetPosition(hpGaugePos);
}
void PlayerHPBar::Update()
{

}
void PlayerHPBar::PostRender(CRenderContext& renderContext)
{

	m_hpGauge.Draw(renderContext);
	m_hpBarBack.Draw(renderContext);

	int HP = g_player->GetHP();
	switch (HP) {
	case 3:
		m_hpHeart[2].Draw(renderContext);
	case 2:
		m_hpHeart[1].Draw(renderContext);
	case 1:
		m_hpHeart[0].Draw(renderContext);
	default:
		break;
	}
}
