#include "stdafx.h"
#include "Bullet.h"
#include "Player.h"
#include "Camera.h"

CSkinModelData	b_OriginSkinModelData;	//スキンモデルデータ
bool			b_flag = false;		//すでに読み込んでいるか

Bullet::Bullet()
{
	//モデルデータをロード(1回だけ)
	if (!b_flag) {
		b_OriginSkinModelData.LoadModelData("Assets/modelData/bullet.x", NULL);
		b_flag = true;
	}
	//CSkinModelを初期化
	modelData.CloneModelData(b_OriginSkinModelData, NULL);
	model.Init(&modelData);

	//デフォルトライトセット
	model.SetLight(&g_defaultLight);

	position = g_player->GetPosition();

	angle = g_player->GetMoveAngle();
	angle.Normalize();			//正規化

	position.x += angle.x * 0.1f;
	position.z += angle.z * 0.1f;

	origin = position;		//最初の位置を記録
}


Bullet::~Bullet()
{
}

void Bullet::Update() {
	CVector3 diff;

	//移動した距離を計算
	diff.Subtract(position, origin);
	float lendth = diff.Length();

	//発砲
	if (lendth > 80.0f || lendth < -80.0f) {
		DeleteGO(this);
	}

	//弾移動
	position.x += angle.x* speed;
	position.z += angle.z* speed;

	model.Update(position, CQuaternion::Identity, CVector3::One);
}

void Bullet::Render(CRenderContext& renderContext) {
	model.Draw(renderContext, gameCamera->GetViewMatrix(), gameCamera->GetProjectionMatrix());
}