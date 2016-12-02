/*
	スコア表示
*/
#include "Number.h"
#pragma once
class DisplayScore : public IGameObject
{
public:
	DisplayScore();
	~DisplayScore();
	void Start() override;
	void Update() override;
	void PostRender(CRenderContext& renderContext) override;
private:
	CSprite		 m_Str;		//HPバーの背景。
	CTexture	m_StrTex;		//HPバーの背景のテクスチャ

	Number*		num[4];
};

