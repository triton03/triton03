/*
	ボス?
*/

#pragma once

#include "Enemy.h"
#include "EnemyBullet.h"

#define SPEED 7.0f

class Boss : public Enemy
{
public:
	Boss();
	~Boss();
	void Update() override;
	void Damage() override;
	void Move();
	void Render(CRenderContext& renderContext) override;

	enum BInfo {
		isWait,
		isWork,
		isDeath,
	};

	BInfo getInfo() {
		return info;
	}

	int GetHP() {
		return state.hp;
	}

private:

	float PlayerDiff();

	float			bulletTimer = 0.0f;		//弾用のタイマー
	float			jumpTimer = 0.0f;		//ジャンプ用のタイマー
	float			timer=0.0f;
	int				dir = 1;
	BInfo			info;

	bool			flag = false;
	bool			isDamage;
	bool			isDelete;

	CVector3		BAngle;
	float			a=0.2f;
};

extern Boss* g_boss;