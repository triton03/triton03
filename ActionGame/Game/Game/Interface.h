/*
	インターフェース
	(HP表示・スコア・タイム)
*/

#pragma once
class Interface : public IGameObject
{
public:
	Interface();
	~Interface();
	void Start() override;
	void Update() override;
	void PostRender(CRenderContext& renderContext) override;
private:
	CSprite  m_InfoBack;		//HPバーの背景。
	CTexture m_InfoBackTex;		//HPバーの背景のテクスチャ
};