/*
	�X�^�[�g���j���[
*/


#pragma once
class StartMenu : public IGameObject
{
public:
	StartMenu();
	~StartMenu();
	void Start() override;
	void Update() override;
	void PostRender(CRenderContext& renderContext) override;
private:
	CSprite				back;			//HP�o�[�B
	CTexture			backTex;		//HP�o�[�̃e�N�X�`���B
	CSprite				moji;
	CTexture			mojiTex;
	CSoundSource		StartSound;		//�T�E���h
	CSoundSource		StartBGM;
	bool				flag = false;
};

