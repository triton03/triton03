/*
	背景表示(仮)
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
	CSprite  m_Back;			//HPゲージ。
	CTexture m_BackTex;		//HPハートのテクスチャ。
};

