#include "stdafx.h"
#include "Number.h"


namespace {
	const CVector2 numSize = { 30.0f, 40.0f };	//�����̃T�C�Y
}

Number::Number()
{

}


Number::~Number()
{
}

void Number::Start()
{
	for (int i = 0; i < 10; i++) {
		char filePath[256];
		sprintf(filePath, "Assets/sprite/number/%d.png", i);
		m_numberTex[i].Load(filePath);

		m_number[i].Init(&m_numberTex[i]);
		m_number[i].SetSize(numSize);
		m_number[i].SetPivot({ 0.5f, 0.5f });
	}
}

//�|�W�V�������Z�b�g����(�\���ʒu)
void Number::Init(CVector2 numPos)
{
	for (int i = 0; i < 10; i++) {
		m_number[i].SetPosition(numPos);
	}
}

void Number::Update()
{

}

//�������Z�b�g(�\������������)
void Number::NumSet(int n)
{
	num = n;
}

void Number::PostRender(CRenderContext& renderContext)
{
	m_number[num].Draw(renderContext);
}