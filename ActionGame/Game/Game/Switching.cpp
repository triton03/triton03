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
	//�w�i
	backTex.Load("Assets/sprite/next.png");
	back.Init(&backTex);
	back.SetSize(backSize);
	back.SetPivot({ 0.5f, 0.5f });		//�s�{�b�g�͒���
	back.SetPosition(backPos);
}
void Switching::Update()
{
	//�������Ȃ�?
}
void Switching::PostRender(CRenderContext& renderContext)
{
	back.Draw(renderContext);
}
