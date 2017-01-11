/*
	ボス?
*/

#pragma once

#include "Enemy.h"
#include "EnemyBullet.h"

#define SPEED 5.0f

class Boss : public Enemy
{
public:
	Boss();
	~Boss();
	void Move();

	enum BInfo {
		isWait,
		isWork,
		inDeath,
	};

	BInfo getInfo() {
		return info;
	}

private:
	float PlayerDiff();

	float			bulletTimer = 0.0f;		//弾用のタイマー
	float			jumpTimer = 0.0f;		//ジャンプ用のタイマー
	float			timer=0.0f;
	int				dir = 1;
	BInfo			info;

	bool			flag = false;
};

