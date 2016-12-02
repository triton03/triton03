/*
	�C���^�[�t�F�[�X
	(HP�\���E�X�R�A�E�^�C��)
*/

#pragma once
class Interface : public IGameObject
{
public:
	Interface();
	~Interface();
	void Start() override;
	void Update() override;
	void PostRender(CRenderContext& renderContext) override;
private:
	CSprite  m_InfoBack;		//HP�o�[�̔w�i�B
	CTexture m_InfoBackTex;		//HP�o�[�̔w�i�̃e�N�X�`��
};