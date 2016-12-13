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
	//”wŒi
	backTex.Load("Assets/sprite/next.png");
	back.Init(&backTex);
	back.SetSize(backSize);
	back.SetPivot({ 0.5f, 0.5f });		//ƒsƒ{ƒbƒg‚Í’†‰›
	back.SetPosition(backPos);
}
void Switching::Update()
{
	//‰½‚à‚µ‚È‚¢?
}
void Switching::PostRender(CRenderContext& renderContext)
{
	back.Draw(renderContext);
}
