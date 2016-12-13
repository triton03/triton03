#include "stdafx.h"
#include "Back.h"
#include "Player.h"
#include "Camera.h"
#include "SceneManager.h"

Back::Back()
{
	skinModelData.LoadModelData("Assets/modelData/Sky.X", NULL);
	skinModel.Init(&skinModelData);
	skinModel.SetLight(&light);

	light.SetAmbinetLight(CVector3(1.2f, 1.0f, 1.0f));
	rotation.SetRotation(CVector3::AxisX, CMath::DegToRad(-15.0f));
}

void Back::Update()
{
	if (scene->isDelete()) {
		DeleteGO(this);
	}

	if (g_player->GetInfo() == Player::isDeath) { return; }
	CVector3 pos;
	pos.x = g_player->GetPosition().x;
	pos.y = 15.0f;
	pos.z = 15.0f;
	skinModel.Update(pos, rotation, CVector3(0.3f, 0.3f, 0.3f));
}
void Back::Render(CRenderContext& renderContext)
{
	skinModel.Draw(renderContext, gameCamera->GetViewMatrix(), gameCamera->GetProjectionMatrix());
}
