#include "stdafx.h"
#include "Player.h"
#include "Camera.h"

Player* g_player;

namespace {
	const CVector3 FirstPosition = { 0.0f, 3.5f ,0.0f};	//最初の位置
}

Player::Player()
{
}

Player::~Player()
{
}

void Player::Start() {
	skinModelData.LoadModelData("Assets/modelData/sorcerer_A.X", NULL);
	skinModel.Init(&skinModelData);
	skinModel.SetLight(&g_defaultLight);			//デフォルトライトを設定。

	position = FirstPosition;
	centralPos.Add(position, central);
	characterController.Init(0.5f, 1.0f, position);	//キャラクタコントローラの初期化。

	//animation.SetAnimationEndTime(AnimationRun, 0.8);
	//animation.PlayAnimation(AnimationStand);

//効果音セット
	JumpSound.Init("Assets/sound/Jump.wav");
	damageSound.Init("Assets/sound/damage.wav");
	deathSound.Init("Assets/sound/death.wav");
	ShotSound.Init("Assets/sound/Shot.wav");
	GetCoinSound.Init("Assets/sound/get.wav");
	HealingSound.Init("Assets/sound/cure.wav");

	state.hp = HP_MAX;
	state.coinNum = 0;
}

//ステータスリセット
void Player::Reset() {
	info = None;

	position = FirstPosition;		//プレイヤーの座標をセット
	characterController.SetPosition(position);

	rotation = CQuaternion::Identity;	//回転
	angle = { 0.0f,0.0f,1.0f };			//回転値?

	state.hp = HP_MAX;
	state.coinNum = 0;

	timer = 0.0f;
}

void Player::Update()
{
	//サウンド更新
	JumpSound.Update();
	damageSound.Update();
	deathSound.Update();
	ShotSound.Update();
	GetCoinSound.Update();
	HealingSound.Update();

	//アニメーション更新
	//animation.Update(1.0f / 30.0f);
	//anim = currentAnimSetNo;

	if (info == isDeath){
		timer += GameTime().GetFrameDeltaTime();

		//死んでから経った時間
		if (timer > 1.3) {
			Reset();
		}
	}
	else if (info == isDamage) {
		timer += GameTime().GetFrameDeltaTime();

		//ダメージ受けてから経った時間
		if (timer > 0.3) {
			info = None;
		}
	}

	//落下死
	if (centralPos.y < -10.0f) {
		state.hp = 0;
		info = isDeath;
		deathSound.Play(false);
	}

	if (info == None) {
		characterController.SetMoveSpeed(Move());	//移動速度を設定
	}


	characterController.Execute();			//キャラクターコントロール実行
	position = characterController.GetPosition();	//実行結果の受け取り
	centralPos.Add(position, central);

//モーションが変わってたら変更する
	//if (currentAnimSetNo != anim) {
	//	animation.PlayAnimation(currentAnimSetNo);
	//}
	skinModel.Update(position, rotation, CVector3::One);

}


//プレイヤーの動き
CVector3 Player::Move()
{
	//キャラクターの移動速度
	CVector3 move = characterController.GetMoveSpeed();
	move.x = -Pad(0).GetLStickXF() * speed;
	move.z = -Pad(0).GetLStickYF() * speed;

	//Aボタンでジャンプ
	if (Pad(0).IsTrigger(enButtonA) && !characterController.IsJump()) {
		move.y = 10.0f;
		characterController.Jump();
		JumpSound.Play(false);	//効果音再生
	}

	if (!isBullet) {
		timer += GameTime().GetFrameDeltaTime();

		//前の弾がでてから経った時間
		if (timer > 0.4) {
			isBullet = true;
			timer = 0.0f;
		}
	}
	//Bボタンで弾発射
	if (Pad(0).IsPress(enButtonB) && isBullet) {
		ShotSound.Play(false);
		bullet[bulletNum] = NewGO<Bullet>(0);
		bulletNum = (bulletNum + 1) % 8;
		isBullet = false;
	}
	if (move.x != 0.0f || move.z != 0.0f)
	{
		angle.x = -Pad(0).GetLStickXF();
		angle.z = -Pad(0).GetLStickYF();

		//向き変更
		rotation.SetRotation(CVector3::AxisY, atan2f(angle.x, angle.z));
	}

	return move;
}

void Player::Render(CRenderContext& renderContext)
{
	skinModel.Draw(renderContext, gameCamera->GetViewMatrix(), gameCamera->GetProjectionMatrix());
}

//プレイヤーと対象の距離を計算して返す
float Player::Distance(CVector3& objectPos) 
{
	CVector3 diff;

	//プレイヤーの座標から敵の座標を減算
	diff.Subtract(centralPos, objectPos);
	//敵とプレイヤーの距離を計算
	return diff.Length();
}

void Player::Damage(CVector3 ePos)
{
	if (info != None) { return; }

	state.hp --;

	if (state.hp == 0) { 
		deathSound.Play(false);
		info = isDeath;
	}
	else {
		info = isDamage;
		damageSound.Play(false);
	}

	CVector3 back;

	//敵とぶつかったらちょっと反動
	back = characterController.GetMoveSpeed();
	back.Subtract(centralPos, ePos);
	back.Normalize();

	//反動のはやさ
	float b_speed = 12.0f;
	back.x *= b_speed;
	back.y *= b_speed;

	characterController.SetMoveSpeed(back);	//移動速度を設定
	characterController.Execute();			//キャラクターコントロール実行
	position = characterController.GetPosition();	//実行結果の受け取り
	centralPos.Add(position, central);
	skinModel.Update(position, rotation, CVector3::One);

	timer = 0.0f;
}

//コイン獲得
void Player::CoinGet() 
{
	state.coinNum++;
	GetCoinSound.Play(false);	//効果音再生
}


//回復アイテム獲得(回復したかを返す)
bool Player::healing()
{	//HPが満タンなので回復できない
	if (state.hp == HP_MAX || info==isDeath) { return false; }

	state.hp++;
	HealingSound.Play(false);
	return true;
}