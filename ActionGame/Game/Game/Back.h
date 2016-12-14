#pragma once

class Back : public IGameObject {
	CSkinModelData	skinModelData;		//�X�L�����f���f�[�^�B
	CSkinModel		skinModel;			//�X�L�����f���B
	CAnimation		animation;			//�A�j���[�V�����B
	CLight			light;				//���C�g�B
	CTexture		normalMap;
public:
	Back();

	~Back(){}

	void Init(const char* modelName);
	void Start() override
	{

	}

	void Update() override;

	void Render(CRenderContext& renderContext) override;

private:
	CQuaternion rotation;
};