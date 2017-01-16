/*
�{�X��HP�\��
*/

#pragma once
class BossHP : public IGameObject
{
public:
	BossHP();
	~BossHP();
	void Start() override;
	void Update() override;
	void PostRender(CRenderContext& renderContext) override;
private:
	CSprite back;
	CTexture backTex;

	CSprite  m_hpHeart[5];		//HP�̃n�[�g�B
	CSprite  m_hpHeartD[5];		//�_���[�W�n�[�g
	CTexture m_hpHeartTex;		//HP�n�[�g�̃e�N�X�`���B
	CTexture m_hpHeartTexD;		//�_���[�W�n�[�g�̃e�N�X�`��
};
