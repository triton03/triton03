/*
	�w�i�\��(��)
*/

#pragma once
class BackGround : public IGameObject
{
public:
	BackGround();
	~BackGround();
	void Start() override;
	void Update() override;
	void PreRender(CRenderContext& renderContext) override;
private:
	CSprite  m_Back;			//HP�Q�[�W�B
	CTexture m_BackTex;		//HP�n�[�g�̃e�N�X�`���B
};

