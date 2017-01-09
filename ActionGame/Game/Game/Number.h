/*
	�����\���N���X
*/

#pragma once

namespace {
	const CVector2 InfoNumSize = { 30.0f, 40.0f };	//�����̃T�C�Y
	const CVector2 ResultNumSize = { 66.0f, 88.0f };	//�����̃T�C�Y
}

enum texState {
	isResult,
	isInfo,
};

class Number : public IGameObject
{
public:
	Number();
	~Number();
	void Init(texState tex, CVector2 numPos, CVector2 numSize= InfoNumSize);
	void Update() override;
	void NumSet(int n);
	void PostRender(CRenderContext& renderContext) override;

private:
	CSprite		m_number[10];		//�����̃X�v���C�g
	CTexture	m_numberTex[10];	//�����̃e�N�X�`��
	int			num=0;				//�\�����鐔��
};