#include "stdafx.h"
#include "Enemy.h"
#include "Player.h"
#include "Camera.h"
#include "Bullet.h"
#include "SceneManager.h"


Enemy::Enemy()
{
}


Enemy::~Enemy()
{
	characterController.RemoveRigidBoby();
}

void Enemy::Init(CVector3 pos)
{
	skinModelData.LoadModelData(filePath, NULL);

	skinModel.Init(&skinModelData);
	skinModel.SetLight(&g_defaultLight);			//デフォルトライトを設定。
	skinModel.SetShadowCasterFlag(true);
	skinModel.SetShadowReceiverFlag(true);

	position = pos;
	centralPos.Add(position, central);

	characterController.Init(0.5f, 1.0f, position);	//キャラクタコントローラの初期化。

	//animation.SetAnimationEndTime(AnimationRun, 0.8);
	//animation.PlayAnimation(AnimationStand);
}

void Enemy::Update()
{
	//アニメーション更新
	//animation.Update(1.0f / 30.0f);
	//anim = currentAnimSetNo;

	//落下死
	if (position.y < -5.0f) {
		state.hp = 0;
	}

	float length = g_player->Distance(centralPos);

	if (length <= 3.0f) {
		g_player->Damage(centralPos);
	}

	this->Damage();

	//HPが0になった
	if (scene->isDelete()|| state.hp <= 0) {
		g_player->SetScore(state.score);
		skinModel.SetShadowCasterFlag(false);
		skinModel.SetShadowReceiverFlag(false);
		DeleteGO(this);
	}

	//動き
	Move();

	//characterController.SetMoveSpeed(move);		//移動速度を設定
	characterController.Execute();					//キャラクターコントロール実行
	position = characterController.GetPosition();	//実行結果の受け取り
	centralPos.Add(position, central);

	skinModel.Update(position, rotation, CVector3::One);
}

void Enemy::Render(CRenderContext& renderContext)
{
	skinModel.Draw(renderContext, gameCamera->GetViewMatrix(), gameCamera->GetProjectionMatrix());
}

//動き
void Enemy::Move()
{

}

void Enemy::Damage()
{
	for (int i = 0; i < 8; i++) {
		if (bullet[i] == nullptr) {	continue;}

		if (bullet[i]->Distance(position) < 3.0) {
			state.hp--;
			bullet[i]->flag = true;
		}
	}
}