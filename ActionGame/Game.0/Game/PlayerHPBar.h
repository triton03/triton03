/*!
 *@brief	プレイヤーのHPバー。
 */

#pragma once

class PlayerHPBar : public IGameObject{
public:
	PlayerHPBar();
	~PlayerHPBar();
	void Start() override;
	void Update() override;
	void PostRender(CRenderContext& renderContext) override;
private:
	CSprite  m_hpHeart[3];		//HPのハート。
	CSprite  m_hpGauge;			//HPゲージ。
	CSprite  m_hpBarBack;		//HPバーの背景。
	CTexture m_hpHeartTex;		//HPハートのテクスチャ。
	CTexture m_hpGaugeTex;		//HPゲージのテクスチャ。
	CTexture m_hpBarBackTex;	//HPバーの背景のテクスチャ
};