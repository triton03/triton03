#include "stdafx.h"
#include "Switching.h"

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
