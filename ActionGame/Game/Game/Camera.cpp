#include "stdafx.h"
#include "Camera.h"
#include "Player.h"
#include "SceneManager.h"
#include "Boss.h"

Camera* gameCamera;

Camera::Camera()
{

}


Camera::~Camera()
{
}

void Camera::Start()
{
	playerDist.Set(0.0f, 15.0f, 30.0f);
	camera.SetPosition(playerDist);
	camera.SetTarget(CVector3::Zero);
	camera.SetFar(100000.0f);
	camera.SetViewAngle(CMath::DegToRad(45.0f));
	camera.Update();
}

void Camera::Update()
{
	//プレイヤーが死んでたら追いかけない
	if (g_player->GetInfo()== Player::isDeath) { return; }

	//ターゲットをプレイヤーに
	target = g_player->GetPosition();
	if (scene->getBossFlag()) {
		target.x = cameraPos.x;
		float bosPos = g_boss->GetPos().x;
		if ((target.x- bosPos) > 15.0) {
			target.x -= 0.145f;
			timer += GameTime().GetFrameDeltaTime();
		}
	}
	else {
		timer = 0.0f;
	}
	
	target.y += 2.0f;

	camera.SetTarget(target);

	cameraPos.Add(target, playerDist);	//ポジション加算
	camera.SetPosition(cameraPos);		//ポジションをセット
	camera.Update();
}