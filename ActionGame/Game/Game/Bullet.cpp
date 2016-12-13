#include "stdafx.h"
#include "Bullet.h"
#include "Player.h"
#include "Camera.h"

CSkinModelData	b_OriginSkinModelData;	//スキンモデルデータ
bool			b_flag = false;		//すでに読み込んでいるか

Bullet*				bullet[BulletMAX];		//弾を格納

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
	flag = false;

	SE = NewGO<CSoundSource>(0);
	SE->Init("Assets/sound/Shot.wav");
	SE->Play(false);
}


Bullet::~Bullet()
{
}

void Bullet::Update() {
	if (flag) { return; }

	CVector3 diff;

	//移動した距離を計算
	diff.Subtract(position, origin);
	float lendth = diff.Length();

	//発砲
	if (lendth > 50.0f || g_player->isStop()) {
		flag = true;
	}

	//弾移動
	position.x += angle.x* speed;
	position.z += angle.z* speed;

	model.Update(position, CQuaternion::Identity, CVector3::One);
}

void Bullet::Render(CRenderContext& renderContext) {
	if (flag) { return; }
	model.Draw(renderContext, gameCamera->GetViewMatrix(), gameCamera->GetProjectionMatrix());
}

//弾と対象の距離を計算
float Bullet::Distance(CVector3& objectPos)
{
	if (flag) { return 10; }

	CVector3 diff;

	//プレイヤーの座標から敵の座標を減算
	diff.Subtract(position, objectPos);
	//敵とプレイヤーの距離を計算
	return diff.Length();
}