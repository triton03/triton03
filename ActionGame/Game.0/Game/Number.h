/*
	�����\���N���X
*/

#pragma once
class Number : public IGameObject
{
public:
	Number();
	~Number();
	void Start() override;
	void Init(CVector2 pos);
	void Update() override;
	void NumSet(int n);
	void PostRender(CRenderContext& renderContext) override;

private:
	CSprite		m_number[10];		//�����̃X�v���C�g
	CTexture	m_numberTex[10];	//�����̃e�N�X�`��
	int			num=0;				//�\�����鐔��
};