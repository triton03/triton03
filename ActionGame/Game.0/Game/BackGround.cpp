#include "stdafx.h"
#include "BackGround.h"


namespace {
	const CVector2 BackSize = { 1280.0f, 720.0f };
}

BackGround::BackGround()
{
}


BackGround::~BackGround()
{
}

void BackGround::Start()
{
	m_BackTex.Load("Assets/sprite/back.png");

	m_Back.Init(&m_BackTex);
	m_Back.SetSize(BackSize);

	//ピボットは左中央。
	m_Back.SetPivot({ 0.5f, 0.5f });

	m_Back.SetPosition({0.0f,0.0f});
}
void BackGround::Update()
{

}
void BackGround::PreRender(CRenderContext& renderContext)
{
	m_Back.Draw(renderContext);
}
