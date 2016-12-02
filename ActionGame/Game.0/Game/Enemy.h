/*
	敵の基本クラス
*/

#pragma once
#include "tkEngine/character/tkCharacterController.h"

class Enemy : public IGameObject
{
public:
	Enemy();
	~Enemy();
	void Init(CVector3 FirstPosition);
	void Reset();
	void Update();
	void Render(CRenderContext& renderContext);
	virtual void Move();			//動き
	void Damage();

protected:
	//モーション
	enum AnimationNo {
		AnimationStand,		//立ち
		AnimationRun,		//走り
		AnimationJump,		//ジャンプ
	};

	char filePath[256];	//ファイルパス

	struct Status
	{
		int					hp;		//体力
		int					score;	//倒したときのスコア
	};

	CSkinModel				skinModel;					//スキンモデル
	CSkinModelData			skinModelData;				//スキンモデルデータ。
	CCharacterController	characterController;		//キャラクタ―コントローラー

	CVector3				position;					//プレイヤーの座標
	CVector3				centralPos;					//プレイヤーの中心の座標
	const CVector3			central = { 0.0f, 1.8f,0.0f };	//プレイヤーの真ん中の高さ

	CQuaternion				rotation = CQuaternion::Identity;	//回転

	//CAnimation		animation;			//アニメーション。
	//AnimationNo		currentAnimSetNo;	//今のモーション
	//AnimationNo		anim;				//変更前のモーション

	Status state;	//敵のステータス
};