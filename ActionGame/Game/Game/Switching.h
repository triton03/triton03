/*
	ステージ切り替え
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
	CSprite				back;			//HPバー。
	CTexture			backTex;		//HPバーのテクスチャ。
	CSprite				moji;
	CTexture			mojiTex;
};

