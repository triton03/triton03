/*
	プレイヤー
*/

#pragma once
#include "tkEngine/character/tkCharacterController.h"
#include "Bullet.h"

class Player : public IGameObject
{
public:
	//プレイヤーの状態
	enum PlayerInfo {
		None,		//通常
		isDamage,	//ダメージ受けた
		isDeath,	//やられちゃった
	};
	const int	HP_MAX = 3;	//プレイヤーの最大HP
	const CVector3	central = { 0.0f, 1.8f,0.0f };	//プレイヤーの真ん中の高さ

/*メンバ関数*/
	Player();
	~Player();
	void Start();
	void Reset();
	void Update();
	CVector3 Move();
	void Render(CRenderContext& renderContext);

	float Distance(CVector3& objectPos);	//プレイヤーとの距離を返す
	void Damage(CVector3 e_pos);		//ダメージ処理
	void CoinGet();
	bool healing();

/*ゲッター*/
	CVector3 GetPosition() {	//プレイヤーの位置を返す
		return centralPos;
	}

	CVector3 GetMoveAngle() {	//向き?を返す
		return angle;
	}

	int GetHP() const		//今のHP返す
	{
		return state.hp;
	}
	PlayerInfo GetInfo() {		//今の状態を返す
		return info;
	}
	float GetTime() {
		return playTime;
	}
	int GetScore() {
		return state.score;
	}

/*セッター*/
	void SetScore(int s) {
		state.score += s;
	}

private:
	//プレイヤーのステータス
	struct Status
	{
		int			hp;			//プレイヤーのHP
		int			score;		//獲得スコア
	};

//モーション
	enum AnimationNo {
		AnimationStand,		//立ち
		AnimationRun,		//走り
		AnimationDeath,		//ジャンプ
	};

/*メンバ変数*/

	CSkinModel				skinModel;					//スキンモデル
	CSkinModelData			skinModelData;				//スキンモデルデータ。
	CCharacterController	characterController;		//キャラクタ―コントローラー

	CVector3				position ;					//プレイヤーの座標
	CVector3				centralPos;					//プレイヤーの中心の座標
	CQuaternion				rotation = CQuaternion::Identity;	//回転
	CVector3				angle = { 0.0f,0.0f,1.0f };			//回転値?

	CAnimation		animation;			//アニメーション。
	AnimationNo		currentAnimSetNo;	//今のモーション
	AnimationNo		anim;				//変更前のモーション

	CSoundSource		JumpSound;		//ジャンプボイス
	CSoundSource		damageSound;	//ダメージボイス
	CSoundSource		deathSound;		//やられボイス
	CSoundSource		ShotSound;		//弾発射
	CSoundSource		GetCoinSound;	//コイン獲得音
	CSoundSource		HealingSound;	//回復音

	Status				state;			//プレイヤーのステータス
	PlayerInfo			info = None;	//プレイヤーの状態

	int					bulletNum = 0;
	bool				isBullet=true;	//弾フラグ

	float				timer = 0.0f;	//タイマー。

	float				playTime = 0.0f;
};
extern Player* g_player;