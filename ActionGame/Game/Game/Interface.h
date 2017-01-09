/*
	インターフェース
	(HP表示・スコア・タイム)
*/

#pragma once
#include "PlayerHPBar.h"
#include "DisplayScore.h"
#include "DisplayTime.h"

class Interface : public IGameObject
{
public:
	Interface();
	~Interface();
	void Start() override;
	void Update() override;
	void DeleteIF();
	void PostRender(CRenderContext& renderContext) override;
private:
	CSprite		 m_InfoBack;		//HPバーの背景。
	CTexture	m_InfoBackTex;		//HPバーの背景のテクスチャ

	PlayerHPBar*		Bar;
	DisplayScore*		DScore;
	DisplayTime*		DTime;
};