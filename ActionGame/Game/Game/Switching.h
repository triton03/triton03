/*
	�X�e�[�W�؂�ւ�
*/

#pragma once
class Switching : public IGameObject
{
public:
	Switching();
	~Switching();
	void Start() override;
	void Update() override;
	void PostRender(CRenderContext& renderContext) override;
private:
	CSprite				back;			//HP�o�[�B
	CTexture			backTex;		//HP�o�[�̃e�N�X�`���B
	CSprite				moji;
	CTexture			mojiTex;
};

