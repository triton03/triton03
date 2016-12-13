#include "stdafx.h"
#include "Player.h"
#include "Camera.h"

Player* g_player;

namespace {
	const CVector3 FirstPosition = { 0.0f, 5.0f ,0.0f};	//最初の位置
}

Player::Player()
{
}

Player::~Player()
{
	characterController.RemoveRigidBoby();
}

void Player::Start() {
	//モデルの読み込み
	skinModelData.LoadModelData("Assets/modelData/sorcerer_A.X", &animation);
	skinModel.Init(&skinModelData);
	skinModel.SetLight(&g_defaultLight);	//デフォルトライトを設定。
	skinModel.SetShadowCasterFlag(true);
	skinModel.SetShadowReceiverFlag(true);

	position = FirstPosition;			//ポジションの設定
	centralPos.Add(position, central);	//モデルの中心を設定
	characterController.Init(0.5f, 1.0f, position);	//キャラクタコントローラの初期化。

	animation.SetAnimationLoopFlag(AnimationDeath, false);
	animation.PlayAnimation(AnimationStand);

//効果音セット
	JumpSound.Init("Assets/sound/Jump.wav");
	damageSound.Init("Assets/sound/damage.wav");
	deathSound.Init("Assets/sound/death.wav");

	state.hp = HP_MAX;
	state.score = 0;
	state.time = 0.0f;

	total.score = 0;
	total.time = 0.0f;
}

//ステータスリセット
void Player::Reset() {
	info = None;

	position = FirstPosition;		//プレイヤーの座標をセット
	characterController.SetPosition(position);
	characterController.SetMoveSpeed(CVector3::Zero);

	rotation = CQuaternion::Identity;	//回転
	angle = { 0.0f,0.0f,1.0f };			//回転値?

	state.score = 0;
	state.time = 0.0f;

	timer = 0.0f;

	currentAnimSetNo = AnimationStand;
	animation.PlayAnimation(currentAnimSetNo);

	StopFlag = false;
	bulletNum = 0;
	for (int i = 0; i < BulletMAX; i++) {
		bullet[i] = nullptr;
	}
}

void Player::Update()
{
	//プレイヤー停止状態
	if (StopFlag) { return; }

	//サウンド更新
	JumpSound.Update();
	damageSound.Update();
	deathSound.Update();

	//アニメーション更新
	animation.Update(1.0f / 30.0f);
	anim = currentAnimSetNo;

	for (int i = 0; i < BulletMAX; i++) {
		if (bullet[i] != nullptr && bullet[i]->GetFlag()) {
			DeleteGO(bullet[i]);
			bullet[i] = bullet[i] = nullptr;
		}
	}

	if (info != isDeath && info != isClear) {
		state.time += GameTime().GetFrameDeltaTime();	//プレイ時間カウント
	}

	if (info == isClear) {
		//クリアしたときの動き

		timer += GameTime().GetFrameDeltaTime();
		if (timer >= 1.0f) {
			rotation = CQuaternion::Identity;	//こっち向き
		}
		if (timer >= 5.0f) {
			total.score += state.score;
			total.time += state.time;
			StopFlag=true;	//プレイヤー停止
		}
		characterController.SetMoveSpeed({0.0f,-5.0f,0.0f});
	}

	//落下死
	if (info!=isDeath && centralPos.y < -10.0f) {
		state.hp = 0;
		info = isDeath;
		deathSound.Play(false);
	}

	if (info == isDeath){
		currentAnimSetNo = AnimationDeath;
		timer += GameTime().GetFrameDeltaTime();

		//死んでから経った時間
		if (timer > 1.3) {
			StopFlag = true;
			characterController.SetPosition(FirstPosition);
		}
	}
	else if (info == isDamage) {
		timer += GameTime().GetFrameDeltaTime();

		//ダメージ受けてから経った時間
		if (timer > 0.5) {
			info = None;
		}
	}

	if (info == None) {
		characterController.SetMoveSpeed(Move());	//移動速度を設定
	}

	characterController.Execute();			//キャラクターコントロール実行
	position = characterController.GetPosition();	//実行結果の受け取り
	centralPos.Add(position, central);

//モーションが変わってたら変更する
	if (currentAnimSetNo != anim) {
		animation.PlayAnimation(currentAnimSetNo);
	}
	skinModel.Update(position, rotation, CVector3::One);
}

//プレイヤーの動き
CVector3 Player::Move()
{
	float		speed = 10.0f;
	//ジャンプ時の重力
	if (characterController.IsJump()) {
		speed = speed * 0.8f;
	}

	//キャラクターの移動速度
	CVector3 move = characterController.GetMoveSpeed();
	move.x = -Pad(0).GetLStickXF() * speed;
	move.z = -Pad(0).GetLStickYF() * speed;

	//Aボタンでジャンプ
	if (Pad(0).IsTrigger(enButtonA) && !characterController.IsJump()) {
		move.y = 13.0f;
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
		bullet[bulletNum] = NewGO<Bullet>(0);
		bulletNum = (bulletNum + 1) % BulletMAX;
		isBullet = false;
	}

	//移動してる
	if (move.x != 0.0f || move.z != 0.0f)
	{
		angle.x = -Pad(0).GetLStickXF();
		angle.z = -Pad(0).GetLStickYF();

		currentAnimSetNo = AnimationRun;

		//向き変更
		rotation.SetRotation(CVector3::AxisY, atan2f(angle.x, angle.z));
	}
	else {
		currentAnimSetNo = AnimationStand;
	}

	return move;
}

void Player::Render(CRenderContext& renderContext)
{
	if (StopFlag) { return; }
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
	float b_speed = 4.3f;
	back.x *= b_speed;
	back.y *= b_speed;

	characterController.SetMoveSpeed(back);	//移動速度を設定
	characterController.Execute();			//キャラクターコントロール実行
	position = characterController.GetPosition();	//実行結果の受け取り
	centralPos.Add(position, central);
	skinModel.Update(position, rotation, CVector3::One);

	timer = 0.0f;
}

//回復アイテム獲得(回復したかを返す)
bool Player::healing()
{	//HPが満タンなので回復できない
	if (state.hp == HP_MAX || info==isDeath) { return false; }

	state.hp++;
	return true;
}