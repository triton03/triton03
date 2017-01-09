/*
	�N���A���̃��U���g���
*/

#pragma once
#include "Number.h"

class TotalResult : public IGameObject
{
public:
	TotalResult();
	~TotalResult();
	void Start() override;
	void Update() override;
	void PostRender(CRenderContext& renderContext) override;
	void DeleteNum();

	bool getFlag()
	{
		return flag;
	}
private:
	const float time_Y = 75.0f;		//�^�C���\�L�̈ʒu(y���W)
	const float score_Y = -50.0f;	//�X�R�A�\�L�̈ʒu(y���W)

	CSprite				back;			//�w�i
	CTexture			backTex;		//�w�i�e�N�X�`���B

	CSoundSource*		Sound;		//�T�E���h
	CSoundSource*		BGM;
	bool				flag = false;

	CSprite		m_colon;		//�R����
	CTexture	m_colonTex;		//�R�����̃e�N�X�`��

	Number*		timeNum[4];
	Number*		scoreNum[5];
};
