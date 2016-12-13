#pragma once

class Back : public IGameObject {
	CSkinModelData	skinModelData;		//スキンモデルデータ。
	CSkinModel		skinModel;			//スキンモデル。
	CAnimation		animation;			//アニメーション。
	CLight			light;				//ライト。
	CTexture		normalMap;
public:
	Back();

	~Back(){}

	void Start() override
	{

	}

	void Update() override;

	void Render(CRenderContext& renderContext) override;

private:
	CQuaternion rotation;
};