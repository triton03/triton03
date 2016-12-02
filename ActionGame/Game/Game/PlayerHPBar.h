/*!
 *@brief	�v���C���[��HP�o�[�B
 */

#pragma once

class PlayerHPBar : public IGameObject
{
public:
	PlayerHPBar();
	~PlayerHPBar();
	void Start() override;
	void Update() override;
	void PostRender(CRenderContext& renderContext) override;
private:
	CSprite  m_hpHeart[3];		//HP�̃n�[�g�B
	CSprite  m_hpBarBack;		//HP�o�[�̔w�i�B
	CTexture m_hpHeartTex;		//HP�n�[�g�̃e�N�X�`���B
	CTexture m_hpBarBackTex;	//HP�o�[�̔w�i�̃e�N�X�`��
};