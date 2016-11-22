/*!
 *@brief	�v���C���[��HP�o�[�B
 */

#pragma once

class PlayerHPBar : public IGameObject{
public:
	PlayerHPBar();
	~PlayerHPBar();
	void Start() override;
	void Update() override;
	void PostRender(CRenderContext& renderContext) override;
private:
	CSprite  m_hpBar;			//HP�o�[�B
	CSprite  m_hpGauge;			//HP�Q�[�W�B
	CSprite  m_hpBarBack;		//HP�o�[�̔w�i�B
	CTexture m_hpBarTex;		//HP�o�[�̃e�N�X�`���B
	CTexture m_hpGaugeTex;		//HP�Q�[�W�̃e�N�X�`���B
	CTexture m_hpBarBackTex;	//HP�o�[�̔w�i�̃e�N�X�`��
};