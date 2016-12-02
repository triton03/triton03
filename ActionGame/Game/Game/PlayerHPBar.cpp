/*
	プレイヤーのHPバー。
 */

#include "stdafx.h"
#include "PlayerHPBar.h"
#include "Player.h"

namespace {
	const CVector2 hpHeartSize = { 80.0f, 60.0f };		//ハートのサイズ
	const CVector2 hpHeartPos1 = { -622.00f, 315.0f };	//1個目のハートの位置
	const CVector2 hpHeartPos2 = { -540.00f, 315.0f };	//2個目のハートの位置
	const CVector2 hpHeartPos3 = { -458.00f, 315.0f };	//3個目のハートの位置
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
	m_hpHeartTexD.Load("Assets/sprite/hp_damage.png");

/*準備処理*/
	for (int i = 0; i < 3; i++) {
		//通常ハート
		m_hpHeart[i].Init(&m_hpHeartTex);
		m_hpHeart[i].SetSize(hpHeartSize);
		m_hpHeart[i].SetPivot({ 0.0f, 0.5f });

		//ダメージハート
		m_hpHeartD[i].Init(&m_hpHeartTexD);
		m_hpHeartD[i].SetSize(hpHeartSize);
		m_hpHeartD[i].SetPivot({ 0.0f, 0.5f });
	}

/*ポジションの設定*/
	// 通常ハート
	m_hpHeart[0].SetPosition(hpHeartPos1);
	m_hpHeart[1].SetPosition(hpHeartPos2);
	m_hpHeart[2].SetPosition(hpHeartPos3);

	//ダメージハート
	m_hpHeartD[0].SetPosition(hpHeartPos1);
	m_hpHeartD[1].SetPosition(hpHeartPos2);
	m_hpHeartD[2].SetPosition(hpHeartPos3);
}
void PlayerHPBar::Update()
{

}
void PlayerHPBar::PostRender(CRenderContext& renderContext)
{
	//プレイヤーの現在HPを取得
	int HP = g_player->GetHP();

	//HP数によって表示を変える
	switch (HP) {
	case 3:
		m_hpHeart[2].Draw(renderContext);
		m_hpHeart[1].Draw(renderContext);
		m_hpHeart[0].Draw(renderContext);
		break;
	case 2:
		m_hpHeartD[2].Draw(renderContext);
		m_hpHeart[1].Draw(renderContext);
		m_hpHeart[0].Draw(renderContext);
		break;
	case 1:
		m_hpHeartD[2].Draw(renderContext);
		m_hpHeartD[1].Draw(renderContext);
		m_hpHeart[0].Draw(renderContext);
		break;
	default:
		m_hpHeartD[2].Draw(renderContext);
		m_hpHeartD[1].Draw(renderContext);
		m_hpHeartD[0].Draw(renderContext);
		break;
	}
}
