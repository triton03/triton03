/*
ボスのHP表示
*/

#pragma once
class BossHP : public IGameObject
{
public:
	BossHP();
	~BossHP();
	void Start() override;
	void Update() override;
	void PostRender(CRenderContext& renderContext) override;
private:
	CSprite back;
	CTexture backTex;

	CSprite  m_hpHeart[5];		//HPのハート。
	CSprite  m_hpHeartD[5];		//ダメージハート
	CTexture m_hpHeartTex;		//HPハートのテクスチャ。
	CTexture m_hpHeartTexD;		//ダメージハートのテクスチャ
};
