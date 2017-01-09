/*
	�C���^�[�t�F�[�X
	(HP�\���E�X�R�A�E�^�C��)
*/

#pragma once
#include "PlayerHPBar.h"
#include "DisplayScore.h"
#include "DisplayTime.h"

class Interface : public IGameObject
{
public:
	Interface();
	~Interface();
	void Start() override;
	void Update() override;
	void DeleteIF();
	void PostRender(CRenderContext& renderContext) override;
private:
	CSprite		 m_InfoBack;		//HP�o�[�̔w�i�B
	CTexture	m_InfoBackTex;		//HP�o�[�̔w�i�̃e�N�X�`��

	PlayerHPBar*		Bar;
	DisplayScore*		DScore;
	DisplayTime*		DTime;
};