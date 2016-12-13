#pragma once



class GameOver : public IGameObject
{
public:
	GameOver();
	~GameOver();
	void Start() override;
	void Update() override;
	void PostRender(CRenderContext& renderContext) override;

	bool isStart() {
		return flag;
	}
	bool GetChoice() {
		return isChoice;
	}

private:
	CSprite				back;			//HPバー。
	CTexture			backTex;		//HPバーのテクスチャ。
	CSprite				choice;			//やじるし
	CTexture			choiceTex;		//やじるしのテクスチャ

	CSoundSource*		SE;

	bool				flag;
	bool				isChoice;
};

