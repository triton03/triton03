/*
	�X�R�A�\��
*/
#include "Number.h"
#pragma once
class DisplayScore : public IGameObject
{
public:
	DisplayScore();
	~DisplayScore();
	void Start() override;
	void Update() override;
	void DeleteNum();
	void PostRender(CRenderContext& renderContext) override;
private:
	CSprite		 m_Str;		//HP�o�[�̔w�i�B
	CTexture	m_StrTex;		//HP�o�[�̔w�i�̃e�N�X�`��

	Number*		num[5];
};

