#include "stdafx.h"
#include "EnemyBullet.h"
#include "Player.h"
#include "Camera.h"
#include "SkeltonMage.h"
#include "SceneManager.h"


CSkinModelData	eb_OriginSkinModelData;	//スキンモデルデータ
bool			eb_flag = false;		//すでに読み込んでいるか

EnemyBullet::EnemyBullet()
{
	//CSkinModelを初期化
	modelData.CloneModelData(eb_OriginSkinModelData, NULL);
	model.Init(&modelData);

	//デフォルトライトセット
	model.SetLight(&g_defaultLight);

	position = CVector3::Zero;
	angle = { 1.0f,0.0f,0.0f };

	position.x +=  0.1f;

	origin = position;		//最初の位置を記録
	flag = false;

	CSoundSource* SE = NewGO<CSoundSource>(0);
	SE->Init("Assets/sound/e_shot.wav");
	SE->Play(false);
}

EnemyBullet::~EnemyBullet()
{
}

void EnemyBullet::Init(CVector3 pos) {
	position = pos;
	origin = position;
}

void EnemyBullet::Update() {
	if (flag) { 
		DeleteGO(this);
	}

	CVector3 diff;

	//移動した距離を計算
	diff.Subtract(position, origin);
	float lendth = diff.Length();

	//発砲
	if (lendth > 50.0f) {
		flag = true;
	}
	if ((scene->isDelete() )||(g_player->Distance(position) <= 3.0f)) {
		g_player->Damage(position);
		flag = true;
	}

	//弾移動
	position.x += (angle.x*speed);
	position.z += (angle.z*speed);

	model.Update(position, CQuaternion::Identity, CVector3::One);
}

void EnemyBullet::Render(CRenderContext& renderContext) {
	if (flag) { return; }
	model.Draw(renderContext, gameCamera->GetViewMatrix(), gameCamera->GetProjectionMatrix());
}