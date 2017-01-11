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
	//�v���C���[������ł���ǂ������Ȃ�
	if (g_player->GetInfo()== Player::isDeath) { return; }

	//�^�[�Q�b�g���v���C���[��
	target = g_player->GetPosition();
	if (scene->getBossFlag()) {
		target.x = cameraPos.x;
		if (timer < 3.0) {
			target.x -= 0.15f;
			timer += GameTime().GetFrameDeltaTime();
		}
	}
	else {
		timer = 0.0f;
	}
	

	camera.SetTarget(target);

	cameraPos.Add(target, playerDist);	//�|�W�V�������Z
	camera.SetPosition(cameraPos);		//�|�W�V�������Z�b�g
	camera.Update();
}