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
	CSprite				back;			//HP�o�[�B
	CTexture			backTex;		//HP�o�[�̃e�N�X�`���B
	CSprite				choice;			//�₶�邵
	CTexture			choiceTex;		//�₶�邵�̃e�N�X�`��

	CSoundSource*		SE;

	bool				flag;
	bool				isChoice;
};

