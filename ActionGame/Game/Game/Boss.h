/*
	�{�X?
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

	float			bulletTimer = 0.0f;		//�e�p�̃^�C�}�[
	float			jumpTimer = 0.0f;		//�W�����v�p�̃^�C�}�[
	float			timer=0.0f;
	int				dir = 1;
	BInfo			info;

	bool			flag = false;
};

