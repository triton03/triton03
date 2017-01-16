/*
	スタートメニュー
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
	CSprite				back;			//HPバー。
	CTexture			backTex;		//HPバーのテクスチャ。
	CSprite				moji;
	CTexture			mojiTex;
	CSprite				moji2;
	CTexture			mojiTex2;

	CSoundSource*		sound;		//サウンド
	CSoundSource*		StartBGM;
	bool				flag = false;
	float				timer = 0.0f;	//タイマー。
};

