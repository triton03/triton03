#include "stdafx.h"
#include "Number.h"


namespace {
	const CVector2 numSize = { 40.2f, 50.2f };	//数字のサイズ
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
		sprintf(filePath, "Assets/modelData/%d.png", i);
		m_numberTex[i].Load(filePath);

		m_number[i].Init(&m_numberTex[i]);
		m_number[i].SetSize(numSize);
		m_number[i].SetPivot({ 0.5f, 0.5f });
	}
}

//ポジションをセットする(表示位置)
void Number::Init(CVector2 numPos)
{
	for (int i = 0; i < 10; i++) {
		m_number[i].SetPosition(numPos);
	}
}

void Number::Update()
{

}

//数字をセット(表示したい数字)
void Number::NumSet(int n)
{
	num = n;
}

void Number::PostRender(CRenderContext& renderContext)
{
	m_number[num].Draw(renderContext);
}