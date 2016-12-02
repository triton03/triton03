/*!
 *@brief	プレイヤーのHPバー。
 */

#pragma once

class PlayerHPBar : public IGameObject
{
public:
	PlayerHPBar();
	~PlayerHPBar();
	void Start() override;
	void Update() override;
	void PostRender(CRenderContext& renderContext) override;
private:
	CSprite  m_hpHeart[3];		//HPのハート。
	CSprite  m_hpHeartD[3];		//ダメージハート
	CTexture m_hpHeartTex;		//HPハートのテクスチャ。
	CTexture m_hpHeartTexD;		//ダメージハートのテクスチャ
};