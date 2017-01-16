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

	bool getFlag() 
	{
		return flag;
	}
private:
	CSprite				back;			//HP�o�[�B
	CTexture			backTex;		//HP�o�[�̃e�N�X�`���B
	CSprite				moji;
	CTexture			mojiTex;
	CSprite				moji2;
	CTexture			mojiTex2;

	CSoundSource*		sound;		//�T�E���h
	CSoundSource*		StartBGM;
	bool				flag = false;
	float				timer = 0.0f;	//�^�C�}�[�B
};

