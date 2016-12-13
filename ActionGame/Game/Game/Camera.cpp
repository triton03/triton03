#include "stdafx.h"
#include "Camera.h"
#include "Player.h"

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
	CVector3 target = g_player->GetPosition();
	target.y += 1.0;
	camera.SetTarget(target);

	CVector3 cameraPos;
	cameraPos.Add(target, playerDist);	//ポジション加算
	camera.SetPosition(cameraPos);		//ポジションをセット
	camera.Update();
}