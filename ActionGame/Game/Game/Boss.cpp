#include "stdafx.h"
#include "Boss.h"
#include "SceneManager.h"
#include "Player.h"
#include "Camera.h"

Boss* g_boss;

Boss::Boss()
{
	skinModelData.LoadModelData("Assets/modelData/sorcerer_D.X", &animation);
	
	state.hp = 5;
	state.score = 450;
	info = isWait;
	isDelete = false;
	isDamage = false;

	//弾のモデルデータをロード(1回だけ)
	if (!eb_flag) {
		eb_OriginSkinModelData.LoadModelData("Assets/modelData/e_bullet.x", NULL);
		eb_flag = true;
	}

	BAngle = { 1.0f,0.0f,0.0f };

	animation.SetAnimationLoopFlag(AnimationDeath, false);
	animation.PlayAnimation(AnimationStand);
}


Boss::~Boss()
{
	scene->setBossFlag(false);
}

void Boss::Update()
{
	//アニメーション更新
	animation.Update(1.0f / 30.0f);

	anim = currentAnimSetNo;

	//HPが0になった
	if (scene->isDelete() || this->isDelete) {
		g_player->SetScore(state.score);
		skinModel.SetShadowCasterFlag(false);
		skinModel.SetShadowReceiverFlag(false);
		DeleteGO(this);
	}

	length = g_player->Distance(centralPos);


	//落下死
	if (centralPos.y < -10.0f) {
		state.hp = 0;
		currentAnimSetNo = AnimationDeath;
		isDelete = true;
	}

	if (length <= 3.0f && info!=isDeath) {
		g_player->Damage(centralPos);
	}

	this->Damage();

	move = characterController.GetMoveSpeed();

	//動き
	Move();

	characterController.SetMoveSpeed(move);		//移動速度を設定
	characterController.Execute();					//キャラクターコントロール実行
	position = characterController.GetPosition();	//実行結果の受け取り
	centralPos.Add(position, central);

	if (anim != currentAnimSetNo) {
		animation.PlayAnimation(currentAnimSetNo,0.3f);
	}

	skinModel.Update(position, rotation, CVector3::One);
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
				CSoundSource* SE = NewGO<CSoundSource>(0);
				SE->Init("Assets/sound/boss_start.wav");
				SE->Play(false);
				g_player->setStop(false);
				info = isWork;
				currentAnimSetNo = AnimationRun;
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

		if (bulletTimer > 0.8f) {
			EnemyBullet* bullet = NewGO<EnemyBullet>(0);
			bullet->Init(centralPos);
			bullet->setAngle(BAngle);
			BAngle.x += a;
			BAngle.z = (1.0 - BAngle.x);
			if ((BAngle.x > 1.0f) || (BAngle.x < 0.5f)) {
				a *= -1.0f;
			}
			bulletTimer = 0.0f;
		}

		bulletTimer += GameTime().GetFrameDeltaTime();


		if (jumpTimer > 1.6f) {
			move.y = 15.0f;
			characterController.Jump();
			jumpTimer = 0.0f;
		}

		jumpTimer += GameTime().GetFrameDeltaTime();
		break;

	case isDeath:
		timer += GameTime().GetFrameDeltaTime();
		move.x = 0.0f;
		move.z = 0.0f;
		if (timer > 3.0f) {
			isDelete = true;
		}
		break;

	}
	
	if (isDamage) {
		timer += GameTime().GetFrameDeltaTime();
		if (timer > 2.0f) {
			isDamage = false;
		}
	}

	if (g_player->GetInfo() == Player::isDeath) {
		scene->setBossFlag(false);
	}
}

void Boss::Damage()
{
	if (g_player->GetInfo() == Player::isClear) { return; }
	if (info != isWork || isDamage) { return; }

	for (int i = 0; i < BulletMAX; i++) {

		if (bullet[i] == nullptr) { continue; }

		if (bullet[i]->Distance(centralPos) < 3.0) {
			state.hp--;
			bullet[i]->SetFlag(true);
			DeleteGO(bullet[i]);
			bullet[i] = nullptr;

			CSoundSource* SE = NewGO<CSoundSource>(0);
			if (state.hp > 0) {
				SE->Init("Assets/sound/boss_hit.wav");
				isDamage = true;
			}
			else {
				SE->Init("Assets/sound/boss_death.wav");
				currentAnimSetNo = AnimationDeath;
				info = isDeath;
			}
			SE->Play(false);
			timer = 0.0f;
		}
	}
}

float Boss::PlayerDiff() {
	CVector3 pos = g_player->GetPosition();
	float r = pos.x - position.x;
	return r;
}

void Boss::Render(CRenderContext& renderContext)
{
	if (length > 40.0f) { return; }
	if (isDamage && (timer<0.3f)) { return; }
	skinModel.Draw(renderContext, gameCamera->GetViewMatrix(), gameCamera->GetProjectionMatrix());
}