#include "stdafx.h"
#include "Switching.h"

namespace {
	const CVector2 backSize = { 1280.0f, 720.f };
	const CVector2 backPos = { 0.0f, 0.0f };
}

Switching::Switching()
{
}


Switching::~Switching()
{
}

void Switching::Start()
{
	//背景
	backTex.Load("Assets/sprite/next.png");
	back.Init(&backTex);
	back.SetSize(backSize);
	back.SetPivot({ 0.5f, 0.5f });		//ピボットは中央
	back.SetPosition(backPos);
}
void Switching::Update()
{
	//何もしない?
}
void Switching::PostRender(CRenderContext& renderContext)
{
	back.Draw(renderContext);
}
