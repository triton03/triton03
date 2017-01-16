/*
スプライト表示用クラス
*/

#pragma once

enum SType {
	start1,
	start2,
	clear1,
	clear2,
};

class ShowSprite : public IGameObject
{
public:
	ShowSprite();
	~ShowSprite();
	void Start() override;
	void Init(SType select);
	void Update() override;
	void PostRender(CRenderContext& renderContext) override;

private:
	CSprite				sprite;			//スプライト
	CTexture			texture;		//テクスチャ
	float timer;
};

