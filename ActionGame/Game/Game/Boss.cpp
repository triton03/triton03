#include "stdafx.h"
#include "Boss.h"
#include "SceneManager.h"
#include "Player.h"

CSkinModelData	BossSkinModelData;	//スキンモデルデータ
bool			Boss_flag = false;		//すでに読み込んでいるか

Boss::Boss()
{
	if (!Boss_flag) {
		BossSkinModelData.LoadModelData("Assets/modelData/sorcerer_D.X", NULL);
		Boss_flag = true;
	}
	skinModelData.CloneModelData(BossSkinModelData, NULL);
	state.hp = 3;
	state.score = 450;
	info = isWait;

	//弾のモデルデータをロード(1回だけ)
	if (!eb_flag) {
		eb_OriginSkinModelData.LoadModelData("Assets/modelData/e_bullet.x", NULL);
		eb_flag = true;
	}
}


Boss::~Boss()
{
	scene->setBossFlag(false);
}

void Boss::Move()
{
	switch (info)
	{
	case isWait:
		if (!flag) {
			CVector3 pos = g_player->GetPosition();
			float r = pos.x - position.x;
			if (r < 30.0f) {
				scene->setBossFlag(true);
				g_player->setStop(true);
				flag = true;
			}
		}

		if (flag) {
			timer += GameTime().GetFrameDeltaTime();
			if (timer > 3.0f) {
				g_player->setStop(false);
				info = isWork;
			}
		}
		break;

	case isWork:
		if (position.z > 9.0) {
			dir = -1;
		}
		else if (position.z < -9.0) {
			dir = 1;
		}
		move.z = SPEED*dir;

		if (bulletTimer > 0.9f) {
			EnemyBullet* bullet = NewGO<EnemyBullet>(0);
			bullet->Init(centralPos);
			bulletTimer = 0.0f;
		}

		bulletTimer += GameTime().GetFrameDeltaTime();


		if (jumpTimer > 1.8f) {
			move.y = 15.0f;
			characterController.Jump();
			jumpTimer = 0.0f;
		}

		jumpTimer += GameTime().GetFrameDeltaTime();
	}
}

float Boss::PlayerDiff() {
	CVector3 pos = g_player->GetPosition();
	float r = pos.x - position.x;
	return r;
}