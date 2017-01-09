/*
	�^�C���\��
*/
#include "Number.h"
#pragma once
class DisplayTime : public IGameObject
{
public:
	DisplayTime();
	~DisplayTime();
	void Start() override;
	void Update() override;
	void DeleteNum();
	void PostRender(CRenderContext& renderContext) override;
private:
	CSprite		 m_Str;		//HP�o�[�̔w�i�B
	CTexture		m_StrTex;		//HP�o�[�̔w�i�̃e�N�X�`��

	CSprite		m_colon;
	CTexture	m_colonTex;

	Number*		num[4];
};

