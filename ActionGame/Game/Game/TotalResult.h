/*
	クリア時のリザルト画面
*/

#pragma once
#include "Number.h"

class TotalResult : public IGameObject
{
public:
	TotalResult();
	~TotalResult();
	void Start() override;
	void Update() override;
	void PostRender(CRenderContext& renderContext) override;
	void DeleteNum();

	bool getFlag()
	{
		return flag;
	}
private:
	const float time_Y = 75.0f;		//タイム表記の位置(y座標)
	const float score_Y = -50.0f;	//スコア表記の位置(y座標)

	CSprite				back;			//背景
	CTexture			backTex;		//背景テクスチャ。

	CSoundSource*		BGM;

	bool				flag = false;

	CSprite		m_colon;		//コロン
	CTexture	m_colonTex;		//コロンのテクスチャ

	Number*		timeNum[4];
	Number*		scoreNum[5];
};
