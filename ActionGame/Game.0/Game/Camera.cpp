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
	playerDist.Set(0.0f, 10.0f, 30.0f);
	camera.SetPosition(playerDist);
	camera.SetTarget(CVector3::Zero);
	camera.SetFar(100000.0f);
	camera.SetViewAngle(CMath::DegToRad(45.0f));
	camera.Update();
}

void Camera::Update()
{
	//�v���C���[������ł���ǂ������Ȃ�
	if (g_player->GetInfo()== Player::isDeath) { return; }

	//�^�[�Q�b�g���v���C���[��
	CVector3 target = g_player->GetPosition();
	camera.SetTarget(target);

	CVector3 cameraPos;
	cameraPos.Add(target, playerDist);	//�|�W�V�������Z
	camera.SetPosition(cameraPos);		//�|�W�V�������Z�b�g
	camera.Update();
}