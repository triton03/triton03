#include "stdafx.h"
#include "BossHP.h"
#include "Boss.h"
#include "SceneManager.h"

#define Heart_Y 235.0f

namespace {
	const CVector2 hpBackSize = { 360.0f, 100.0f };		//�n�[�g�̃T�C�Y
	const CVector2 hpBackPos = { 150.00f, 250 };	//1�ڂ̃n�[�g�̈ʒu

	const CVector2 hpHeartSize = { 64.0f, 52.0f };		//�n�[�g�̃T�C�Y
	const CVector2 hpHeartPos1 = { 160.00f, Heart_Y };	//1�ڂ̃n�[�g�̈ʒu
	const CVector2 hpHeartPos2 = { 230.00f, Heart_Y };	//2�ڂ̃n�[�g�̈ʒu
	const CVector2 hpHeartPos3 = { 300.00f, Heart_Y };	//3�ڂ̃n�[�g�̈ʒu
	const CVector2 hpHeartPos4 = { 370.00f, Heart_Y };	//4�ڂ̃n�[�g�̈ʒu
	const CVector2 hpHeartPos5 = { 440.00f, Heart_Y };	//5�ڂ̃n�[�g�̈ʒu
}
BossHP::BossHP()
{
}


BossHP::~BossHP()
{
}

void BossHP::Start()
{
	m_hpHeartTex.Load("Assets/sprite/boss_heart.png");
	m_hpHeartTexD.Load("Assets/sprite/boss_damage.png");
	backTex.Load("Assets/sprite/bossHP_back.png");

	/*��������*/
	back.Init(&backTex);
	back.SetSize(hpBackSize);
	back.SetPivot({ 0.0f, 0.5f });
	back.SetPosition(hpBackPos);

	for (int i = 0; i < 5; i++) {
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
	m_hpHeart[3].SetPosition(hpHeartPos4);
	m_hpHeart[4].SetPosition(hpHeartPos5);

	//�_���[�W�n�[�g
	m_hpHeartD[0].SetPosition(hpHeartPos1);
	m_hpHeartD[1].SetPosition(hpHeartPos2);
	m_hpHeartD[2].SetPosition(hpHeartPos3);
	m_hpHeartD[3].SetPosition(hpHeartPos4);
	m_hpHeartD[4].SetPosition(hpHeartPos5);
}
void BossHP::Update()
{
	if (!scene->getBossFlag()) {
		DeleteGO(this);
	}
}
void BossHP::PostRender(CRenderContext& renderContext)
{
	back.Draw(renderContext);

	int HP = g_boss->GetHP();


	//HP���ɂ���ĕ\����ς���
	for (int i = 0; i < 5; i++) {
		if (HP >= (i+1)) {
			m_hpHeart[i].Draw(renderContext);
		}
		else {
			m_hpHeartD[i].Draw(renderContext);
		}
	};

	/*
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
	*/
}
