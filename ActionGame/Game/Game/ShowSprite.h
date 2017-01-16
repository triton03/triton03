/*
�X�v���C�g�\���p�N���X
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
	CSprite				sprite;			//�X�v���C�g
	CTexture			texture;		//�e�N�X�`��
	float timer;
};

