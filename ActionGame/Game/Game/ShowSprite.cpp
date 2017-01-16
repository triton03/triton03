#include "stdafx.h"
#include "ShowSprite.h"


namespace {
	const CVector2 SSize = { 558.3f, 100.f };
	const CVector2 SPos = { 0.0f, 120.0f };
}

ShowSprite::ShowSprite()
{
}


ShowSprite::~ShowSprite()
{
}

void ShowSprite::Start()
{

}
void ShowSprite::Init(SType select)
{
	switch (select) {
	case start1:
		//背景
		texture.Load("Assets/sprite/start1.png");
		sprite.Init(&texture);
		sprite.SetSize(SSize);
		sprite.SetPivot({ 0.5f, 0.5f });		//ピボットは中央
		sprite.SetPosition(SPos);
		break;

	case start2:
		//背景
		texture.Load("Assets/sprite/start2.png");
		sprite.Init(&texture);
		sprite.SetSize(SSize);
		sprite.SetPivot({ 0.5f, 0.5f });		//ピボットは中央
		sprite.SetPosition(SPos);
		break;

	case clear1:
		texture.Load("Assets/sprite/clear1.png");
		sprite.Init(&texture);
		sprite.SetSize(SSize);
		sprite.SetPivot({ 0.5f, 0.5f });		//ピボットは中央
		sprite.SetPosition(SPos);
		break;

	case clear2:
		texture.Load("Assets/sprite/clear2.png");
		sprite.Init(&texture);
		sprite.SetSize(SSize);
		sprite.SetPivot({ 0.5f, 0.5f });		//ピボットは中央
		sprite.SetPosition(SPos);
		break;
	}
}

void ShowSprite::Update()
{
	timer += GameTime().GetFrameDeltaTime();
	if (timer > 2.5f) {
		DeleteGO(this);
	}

}
void ShowSprite::PostRender(CRenderContext& renderContext)
{
	sprite.Draw(renderContext);
}
