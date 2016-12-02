/*
	�v���C���[��HP�o�[�B
 */

#include "stdafx.h"
#include "PlayerHPBar.h"
#include "Player.h"

namespace {
	const CVector2 hpHeartSize = { 80.0f, 60.0f };		//�n�[�g�̃T�C�Y
	const CVector2 hpHeartPos1 = { -622.00f, 315.0f };	//1�ڂ̃n�[�g�̈ʒu
	const CVector2 hpHeartPos2 = { -540.00f, 315.0f };	//2�ڂ̃n�[�g�̈ʒu
	const CVector2 hpHeartPos3 = { -458.00f, 315.0f };	//3�ڂ̃n�[�g�̈ʒu
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

/*��������*/
	for (int i = 0; i < 3; i++) {
		//�ʏ�n�[�g
		m_hpHeart[i].Init(&m_hpHeartTex);
		m_hpHeart[i].SetSize(hpHeartSize);
		m_hpHeart[i].SetPivot({ 0.0f, 0.5f });

		//�_���[�W�n�[�g
		m_hpHeartD[i].Init(&m_hpHeartTexD);
		m_hpHeartD[i].SetSize(hpHeartSize);
		m_hpHeartD[i].SetPivot({ 0.0f, 0.5f });
	}

/*�|�W�V�����̐ݒ�*/
	// �ʏ�n�[�g
	m_hpHeart[0].SetPosition(hpHeartPos1);
	m_hpHeart[1].SetPosition(hpHeartPos2);
	m_hpHeart[2].SetPosition(hpHeartPos3);

	//�_���[�W�n�[�g
	m_hpHeartD[0].SetPosition(hpHeartPos1);
	m_hpHeartD[1].SetPosition(hpHeartPos2);
	m_hpHeartD[2].SetPosition(hpHeartPos3);
}
void PlayerHPBar::Update()
{

}
void PlayerHPBar::PostRender(CRenderContext& renderContext)
{
	//�v���C���[�̌���HP���擾
	int HP = g_player->GetHP();

	//HP���ɂ���ĕ\����ς���
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
